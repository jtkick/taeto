#include "taeto/engine.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <deque>
#include <memory>

#include <glm/glm.hpp>
#include "spdlog/spdlog.h"

#include "taeto/components/display_pixel.hpp"

#include "taeto/objects/camera.hpp"
#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/objects/lights/light.hpp"
#include "taeto/objects/object.hpp"
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

    // Sprites to be rendered
    std::vector<std::weak_ptr<Object>> objects_;

    // Windows to be displayed
    std::vector<std::weak_ptr<Object>> widgets_;

    // Engine camera
    Camera camera_ = Camera(10);

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
    return camera_;
}

float key_state(int id)
{
    return input_system_->key_state(id);
}

void load_object(std::weak_ptr<Object> object)
{
    spdlog::debug("Adding object to engine.");

    // Get shared pointer to object
    std::shared_ptr<Object> o;
    if (!(o = object.lock()))
        return;

    // Load object to main vector
    objects_.push_back(object);
}

void load_widget(std::weak_ptr<Object> widget)
{
    spdlog::debug("Adding widget to engine.");

    // Get shared pointer to widget
    std::shared_ptr<Object> w;
    if (!(w = widget.lock()))
        return;

    // Load widget to main vector
    widgets_.push_back(widget);
}

void run()
{
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
    spdlog::info("Done setting up engine.");

    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int window_height_ = size.ws_row;
    int window_width_ = size.ws_col;

    // Create new frame for rendering and displaying game world
    taeto::DisplayPixelFrame frame = taeto::DisplayPixelFrame(
        glm::uvec2(window_width_, window_height_));
    spdlog::debug("Frame dimensions set.");

    // Start rendering
    while (true)
    {
        // Update frame sizes if window size changed
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        int window_height_ = size.ws_row;
        int window_width_ = size.ws_col;
        frame.resize(glm::uvec2(window_width_, window_height_));
        spdlog::debug("Frame dimensions resized.");

        // For calculating frame rate and passing to objects, get time since
        // the last frame was rendered
        spdlog::debug("Getting frame duration.");
        last_frame_duration_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ) - last_frame_start_time_;
        last_frame_start_time_ =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        // Clear out all dead pointers from engine
        spdlog::debug("Clearing out all dead pointers.");
        for (int i = objects_.size()-1; i >= 0; --i)
            if (objects_.at(i).expired())
                objects_.erase(objects_.begin() + i);
        for (int i = lights_.size()-1; i >= 0; --i)
            if (lights_.at(i).expired())
                lights_.erase(lights_.begin() + i);


        ////////////////////////////////////////////////////////////////
        ////                       INPUT STEP                       ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Polling inputs.");
        input_system_->poll_inputs();


        ////////////////////////////////////////////////////////////////
        ////                     ANIMATION STEP                     ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Telling objects to animate.");
        for (std::weak_ptr<Object> object : objects_)
            // Get pointer if not dead
            if (std::shared_ptr<Object> o = object.lock())
                o->animate();


        ////////////////////////////////////////////////////////////////
        ////                      PHYSICS STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Physics
        spdlog::debug("Applying forces to sprites.");
        physics_system_.apply_forces(objects_);
        physics_system_.apply_speeds(objects_);


        ////////////////////////////////////////////////////////////////
        ////                      RENDER STEP                       ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Rendering new frame.");
        render_system_.render_frame(frame, camera_, objects_, objects_);


        ////////////////////////////////////////////////////////////////
        ////                       WINDOW STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Draw all windows on the rendered frame
        for (std::weak_ptr<IRenderable> widget : widgets_)
        {
            if (std::shared_ptr<IRenderable> w = widget.lock())
            {
                DisplayPixelFrame render = w->render();
                frame.apply(
                    render,
                    w->position(),
                    false,
                    [](DisplayPixel& a, DisplayPixel& b)->DisplayPixel&
                    {
                        a.c = b.c;
                        a.fg_color = taeto::mix_colors(a.fg_color, b.fg_color);
                        a.bg_color = taeto::mix_colors(a.bg_color, b.bg_color);
                        a.bold = b.bold;
                        a.italic = b.italic;
                        a.underline = b.underline;
                        a.strikethrough = b.strikethrough;
                        return a;
                    }
                );
            }
        }


        ////////////////////////////////////////////////////////////////
        ////                       DEBUG STEP                       ////
        ////////////////////////////////////////////////////////////////

        // Print debug information if flag is true
        if (debug_mode_on_)
        {
            frame.add_string(
                0, 0, "FPS: " + std::to_string((int)(1000.0/last_frame_duration_.count())));
            frame.add_string(
                1, 0, "NUM SPRITES: " + std::to_string(objects_.size()));
            frame.add_string(
                2, 0, "NUM LIGHTS: " + std::to_string(lights_.size()));
            frame.add_string(
                3, 0, "NUM WIDGETS: " + std::to_string(widgets_.size()));
            frame.add_string(
                4, 0,
                "CAMERA LOCATION: ("
                    + std::to_string((int)camera_.position().z) + ", "
                    + std::to_string((int)camera_.position().y) + ", "
                    + std::to_string((int)camera_.position().x) + ")");
            frame.add_string(
                5, 0,
                "FRAME DIMENSIONS: "
                    + std::to_string(frame.height()) + "x"
                    + std::to_string(frame.width()));
            frame.add_string(
                6, 0, "CURRENT FRAME: " + std::to_string(frame_number_++));
        }

        spdlog::debug("Displaying frame.");
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
