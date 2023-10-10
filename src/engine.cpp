#include "engine.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <deque>
#include <memory>

#include "spdlog/spdlog.h"

#include "components/display_pixel.hpp"

#include "components/camera.hpp"
#include "frames/display_pixel_frame.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/light.hpp"
#include "object/object.hpp"
#include "object/sprite.hpp"
#include "scenes/scene.hpp"
#include "systems/audio_system.hpp"
#include "systems/input_system.hpp"
#include "systems/display_system.hpp"
#include "systems/render_system/ray_cast_render_system.hpp"
#include "systems/physics_system.hpp"

namespace taeto
{

// Private data
namespace {

    // Sprites to be rendered
    std::vector<std::weak_ptr<taeto::Sprite>> sprites_;

    // Light sources
    std::vector<std::weak_ptr<taeto::Light>> lights_;

    // Currently loaded scene
    std::shared_ptr<Scene> scene_;

    // Engine camera
    taeto::Camera camera_ = taeto::Camera(10);

    // If set to true, engine will display FPS in top left corner
    bool debug_mode_on_ = true;

    // Time last the last frame was rendered, used for calculating FPS
    std::chrono::milliseconds last_frame_start_time_;
    std::chrono::milliseconds last_frame_duration_;

    // For keeping track of frame rate
    unsigned long long frame_number_;
    std::deque<std::chrono::milliseconds> frame_times_;
    unsigned long current_fps_;

    // Systems
    taeto::InputSystem input_system_ = taeto::InputSystem(logger_);
}

std::shared_ptr<bool> get_button_reference(int id)
{
    return input_system_.get_button_reference(id);
}

taeto::Camera& get_camera()
{
    return camera_;
}

void load_sprite(std::weak_ptr<taeto::Sprite> sprite)
{
    spdlog::debug("Adding object to engine.");

    // Get shared pointer to object
    std::shared_ptr<taeto::Sprite> s;
    if (!(s = sprite.lock()))
        return;

    // Load object to main vector
    sprites_.push_back(sprite);
}

void load_light(std::weak_ptr<taeto::Light> light)
{
    spdlog::debug("Adding light to engine.");

    // Get shared pointer to object
    std::shared_ptr<taeto::Light> l;
    if (!(l = light.lock()))
        return;

    // Load object to main vector
    lights_.push_back(light);
}

void load_scene(std::shared_ptr<Scene> scene)
{
    sprites_.clear();
    lights_.clear();

    spdlog::debug("Loading scene.");
    scene_ = scene;
    scene_->load();
}

void run()
{
    // Declare and start all systems
    spdlog::info("Constructing engine systems.");
    taeto::AudioSystem audio_system_ = taeto::AudioSystem();
    // taeto::InputSystem input_system_ = taeto::InputSystem();
    taeto::RayCastRenderSystem render_system_ = taeto::RayCastRenderSystem();
    taeto::DisplaySystem display_system_ = taeto::DisplaySystem();
    taeto::PhysicsSystem physics_system_ = taeto::PhysicsSystem();
    spdlog::info("Done setting up engine.");

    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int window_height_ = size.ws_row;
    int window_width_ = size.ws_col;

    // Create new frame for rendering and displaying game world
    taeto::DisplayPixelFrame frame =
        taeto::DisplayPixelFrame(
            window_height_, window_width_);
    spdlog::debug("Frame dimensions set.");

    // Start rendering
    while (true)
    {
        // Update frame sizes if window size changed
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        int window_height_ = size.ws_row;
        int window_width_ = size.ws_col;
        frame.resize(window_height_, window_width_);
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
        for (int i = sprites_.size()-1; i >= 0; --i)
            if (sprites_.at(i).expired())
                sprites_.erase(sprites_.begin() + i);
        for (int i = lights_.size()-1; i >= 0; --i)
            if (lights_.at(i).expired())
                lights_.erase(lights_.begin() + i);


        ////////////////////////////////////////////////////////////////
        ////                       INPUT STEP                       ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Polling inputs.");
        input_system_.poll_inputs();


        ////////////////////////////////////////////////////////////////
        ////                     ANIMATION STEP                     ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Telling sprites to animate.");
        for (std::weak_ptr<taeto::Sprite> sprite : sprites_)
            // Get pointer if not dead
            if (std::shared_ptr<taeto::Sprite> s = sprite.lock())
                // s->animate(last_frame_duration_);
                s->animate();

        spdlog::debug("Telling scene to animate.");
        if (scene_)
            scene_->animate();


        ////////////////////////////////////////////////////////////////
        ////                      PHYSICS STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Physics
        spdlog::debug("Applying forces to sprites.");
        physics_system_.detect_collisions(sprites_);


        ////////////////////////////////////////////////////////////////
        ////                      RENDER STEP                       ////
        ////////////////////////////////////////////////////////////////

        spdlog::debug("Rendering new frame.");
        render_system_.render_frame(frame, camera_, sprites_, lights_);


        ////////////////////////////////////////////////////////////////
        ////                  POST-PROCESSING STEP                  ////
        ////////////////////////////////////////////////////////////////

        // Print debug information if flag is true
        if (debug_mode_on_)
        {
            frame.add_string(
                0, 0, "FPS: " + std::to_string((int)(1000.0/last_frame_duration_.count())));
            frame.add_string(
                1, 0, "NUM SPRITES: " + std::to_string(sprites_.size()));
            frame.add_string(
                2, 0, "NUM LIGHTS: " + std::to_string(lights_.size()));
            frame.add_string(
                3, 0,
                "CAMERA LOCATION: ("
                    + std::to_string((int)camera_.position().z()) + ", "
                    + std::to_string((int)camera_.position().y()) + ", "
                    + std::to_string((int)camera_.position().x()) + ")");
            frame.add_string(
                4, 0,
                "FRAME DIMENSIONS: "
                    + std::to_string(frame.height()) + "x"
                    + std::to_string(frame.width()));
            frame.add_string(
                5, 0, "CURRENT FRAME: " + std::to_string(frame_number_++));
        }

        spdlog::debug("Displaying frame.");
        display_system_.display_frame(frame);
    }

    endwin();
}

void set_debug_mode(bool debug_mode_on)
{
    debug_mode_on_ = debug_mode_on;
}

}   // namespace taeto
