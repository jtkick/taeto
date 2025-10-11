#include "taeto/engine.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <deque>
#include <limits>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "taeto/components/display_pixel.hpp"

#include "taeto/objects/camera.hpp"
#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/objects/object.hpp"
#include "taeto/objects/ianimated.hpp"
#include "taeto/objects/ichemical.hpp"
#include "taeto/objects/iemissive.hpp"
#include "taeto/objects/ilight.hpp"
#include "taeto/objects/iphysical.hpp"
#include "taeto/objects/ipositionable.hpp"
#include "taeto/objects/irenderable.hpp"
#include "taeto/scenes/scene.hpp"
#include "taeto/systems/audio_system.hpp"
#include "taeto/systems/input_systems/input_system.hpp"
#include "taeto/systems/input_systems/sfml_input_system.hpp"
#include "taeto/systems/display_systems/display_system.hpp"
#include "taeto/systems/display_systems/stdout_display_system/stdout_display_system.hpp"
#include "taeto/systems/render_system/ray_cast_render_system.hpp"
#include "taeto/systems/physics_system.hpp"
#include "taeto/widgets/widget.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

// Private data
namespace {

    EngineSettings settings_;

    // All objects that exist in the engine
    std::vector<std::weak_ptr<Object>> objects_;
    // TODO: ENSURE WE ONLY HAVE ONE POINTER TO AN OBJECT
    std::vector<std::weak_ptr<IAnimated>> animateds_;
    std::vector<std::weak_ptr<IPhysical>> physicals_;
    std::vector<std::weak_ptr<ISprite>> world_space_sprites_;
    std::vector<std::weak_ptr<ILight>> world_space_lights_;

    // Windows to be displayed
    std::vector<std::weak_ptr<ISprite>> screen_space_sprites_;
    std::vector<std::weak_ptr<ILight>> screen_space_lights_;

    // Engine camera
    Camera world_space_camera_ = Camera(10);

    // To keep things simple, we're going to use the existing rendering system
    // to render the windows by using a camera that flattens everything.
    Camera screen_space_camera_ = Camera(std::numeric_limits<double>::infinity());
    // TODO: TRY PUSHING THIS BACK TO NEGATIVE INFINITY
    // screen_space_camera_.position().z = -100;

    // If set to true, engine will display FPS in top left corner
    bool debug_mode_on_ = false;

    // Time last the last frame was rendered, used for calculating FPS
    std::chrono::milliseconds last_frame_start_time_;
    std::chrono::milliseconds last_frame_duration_;

    // For keeping track of frame rate
    unsigned long long frame_number_;
    std::deque<std::chrono::milliseconds> frame_times_;
    unsigned long current_fps_;

    // Systems
    std::unique_ptr<taeto::InputSystem> input_system_ =
        std::make_unique<taeto::SFMLInputSystem>(taeto::SFMLInputSystem());
}

Camera& camera()
{
    return world_space_camera_;
}

float key_state(int id)
{
    return input_system_->key_state(id);
}

void load_object(std::weak_ptr<Object> object, Context context)
{
    // We're going to keep caches of each object in regards to any interface
    // it might implement. This allows us to pass objects to systems, in a way
    // that guarantees it implements the interface, and is still valid. This
    // prevents constant checking that the pointer is alive, and that the
    // object implements the interface.
    spdlog::debug("Adding object to engine.");
    if (auto locked = object.lock())
    {
        objects_.push_back(object);
        if (auto obj = std::dynamic_pointer_cast<IAnimated>(locked))
            animateds_.push_back(obj);
        if (auto obj = std::dynamic_pointer_cast<IPhysical>(locked))
            physicals_.push_back(obj);
        if (auto obj = std::dynamic_pointer_cast<ISprite>(locked))
        {
            if (context == Context::kWorldSpace)
                world_space_sprites_.push_back(obj);
            else if (context == Context::kScreenSpace)
                screen_space_sprites_.push_back(obj);
            // TODO: MAKE SURE SHADER IS ONLY LOADED ONCE
            for (auto shader : obj->shaders())
                if (auto locked_shader = shader.lock())
                    if (auto s = std::dynamic_pointer_cast<IAnimated>(locked_shader))
                        animateds_.push_back(s);
        }
        if (auto obj = std::dynamic_pointer_cast<ILight>(locked))
            if (context == Context::kWorldSpace)
                world_space_lights_.push_back(obj);
            else if (context == Context::kScreenSpace)
                screen_space_lights_.push_back(obj);

        // Allow object to do its own loading
        locked->load();
    }
}

void run()
{
    // Create a logger, don't print to the screen because it messes with the
    // display system
    auto logger = spdlog::basic_logger_mt("taeto", "logs/taeto.log");
    spdlog::set_default_logger(logger);
    // spdlog::register_logger(logger);

    // Declare and start all systems
    spdlog::info("Constructing engine systems.");
    taeto::AudioSystem audio_system_ = taeto::AudioSystem();
    // taeto::InputSystem input_system_ = taeto::InputSystem();
    taeto::RayCastRenderSystem render_system_ =
        taeto::RayCastRenderSystem(settings_.render_settings);
    std::shared_ptr<taeto::DisplaySystem> display_system_ =
        std::make_shared<taeto::StdoutDisplaySystem>(
            taeto::StdoutDisplaySystem());
    taeto::PhysicsSystem physics_system_ = taeto::PhysicsSystem();
    logger->info("Done setting up engine.");

    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int window_height_ = size.ws_row;
    int window_width_ = size.ws_col;

    // Create new frame for rendering and displaying game world
    taeto::DisplayPixelFrame frame = taeto::DisplayPixelFrame(
        glm::uvec2(window_width_, window_height_));
    logger->debug("Frame dimensions set.");

    // TODO: DO SOMETHING WITH THIS
    // Push the window camera back
    screen_space_camera_.position().z = -std::numeric_limits<double>::infinity();
    settings_.render_settings.render_distance = std::numeric_limits<double>::infinity();

    // Start rendering
    while (true)
    {
        // Update frame sizes if window size changed
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        int window_height_ = size.ws_row;
        int window_width_ = size.ws_col;
        frame.resize(glm::uvec2(window_width_, window_height_));
        logger->debug("Frame dimensions resized.");

        // For calculating frame rate and passing to objects, get time since
        // the last frame was rendered
        logger->debug("Getting frame duration.");
        last_frame_duration_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ) - last_frame_start_time_;
        last_frame_start_time_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        ////////////////////////////////////////////////////////////////
        ////                       INPUT STEP                       ////
        ////////////////////////////////////////////////////////////////

        logger->debug("Polling inputs.");
        input_system_->poll_inputs();


        ////////////////////////////////////////////////////////////////
        ////                     ANIMATION STEP                     ////
        ////////////////////////////////////////////////////////////////

        logger->debug("Telling objects to animate.");
        for (auto object : animateds_)
            // Get pointer if not dead
            if (auto locked = object.lock())
                locked->animate();


        ////////////////////////////////////////////////////////////////
        ////                      PHYSICS STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Physics
        logger->debug("Applying forces to sprites.");
        physics_system_.apply_forces(physicals_);
        physics_system_.move_objects(physicals_);


        ////////////////////////////////////////////////////////////////
        ////                      RENDER STEP                       ////
        ////////////////////////////////////////////////////////////////

        // Clear the frame before rendering
        for (int i = 0; i < frame.height(); i++)
            for (int j = 0; j < frame.width(); j++)
                frame.at({j, i}).clear();

        logger->debug("Rendering new frame.");
        render_system_.render_frame(
            frame, world_space_camera_,
            world_space_sprites_, world_space_lights_
        );

        // spdlog::debug("Rendering windows.");
        // // Gather widgets
        // std::vector<std::weak_ptr<Object>> screen_space_sprites;
        // std::copy_if(
        //     screen_space_objects_.begin(), screen_space_objects_.end(),
        //     std::back_inserter(screen_space_sprites),
        //     [](std::weak_ptr<Object> obj){
        //         if (auto locked = obj.lock())
        //             return std::dynamic_pointer_cast<IPositionable>(locked) &&
        //                 std::dynamic_pointer_cast<IRenderable>(locked);
        //     }
        // );

        // std::vector<std::weak_ptr<Object>> screen_space_lights;
        // std::copy_if(
        //     screen_space_objects_.begin(), screen_space_objects_.end(),
        //     std::back_inserter(screen_space_lights),
        //     [](std::weak_ptr<Object> obj){
        //         if (auto locked = obj.lock())
        //             return std::dynamic_pointer_cast<IPositionable>(locked) &&
        //                 std::dynamic_pointer_cast<IEmissive>(locked);
        //     }
        // );

        render_system_.render_windows(frame, screen_space_sprites_);

        ////////////////////////////////////////////////////////////////
        ////                       WINDOW STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Draw all windows on the rendered frame
        // for (std::weak_ptr<IRenderable> widget : widgets_)
        // {
        //     if (std::shared_ptr<IRenderable> w = widget.lock())
        //     {
        //         DisplayPixelFrame render = w->render();
        //         frame.apply(
        //             render,
        //             w->position(),
        //             false,
        //             [](DisplayPixel& a, DisplayPixel& b)->DisplayPixel&
        //             {
        //                 a.c = b.c;
        //                 a.fg_color = taeto::mix_colors(a.fg_color, b.fg_color);
        //                 a.bg_color = taeto::mix_colors(a.bg_color, b.bg_color);
        //                 a.bold = b.bold;
        //                 a.italic = b.italic;
        //                 a.underline = b.underline;
        //                 a.strikethrough = b.strikethrough;
        //                 return a;
        //             }
        //         );
        //     }
        // }


        ////////////////////////////////////////////////////////////////
        ////                       DEBUG STEP                       ////
        ////////////////////////////////////////////////////////////////

        // Print debug information if flag is true
        if (debug_mode_on_)
        {
            frame.add_string(
                0, 0, "FPS: " + std::to_string((int)(1000.0/last_frame_duration_.count())));
            frame.add_string(
                1, 0, "NUM SPRITES: " + std::to_string(world_space_sprites_.size()));
            frame.add_string(
                2, 0, "NUM LIGHTS: " + std::to_string(world_space_lights_.size()));
            frame.add_string(
                3, 0, "NUM WINDOWS: " + std::to_string(screen_space_sprites_.size()));
            frame.add_string(
                4, 0,
                "CAMERA LOCATION: ("
                    + std::to_string((int)world_space_camera_.position().z) + ", "
                    + std::to_string((int)world_space_camera_.position().y) + ", "
                    + std::to_string((int)world_space_camera_.position().x) + ")");
            frame.add_string(
                5, 0,
                "FRAME DIMENSIONS: "
                    + std::to_string(frame.height()) + "x"
                    + std::to_string(frame.width()));
            frame.add_string(
                6, 0, "CURRENT FRAME: " + std::to_string(frame_number_++));
        }

        logger->debug("Displaying frame.");
        display_system_->display_frame(frame);
    }

    endwin();
}

void debug_mode(bool debug_mode_on)
{
    debug_mode_on_ = debug_mode_on;
}

bool debug_mode()
{
    return debug_mode_on_;
}

EngineSettings& settings()
{
    return settings_;
}

}   // namespace taeto
