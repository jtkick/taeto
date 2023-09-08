#include "engine.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include <deque>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "components/camera.hpp"
#include "frames/display_pixel_frame.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/object.hpp"
#include "scenes/scene.hpp"
#include "systems/audio_system.hpp"
#include "systems/input_system.hpp"
#include "systems/display_system.hpp"
#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"

namespace taeto
{

// Private data
namespace {

    std::shared_ptr<spdlog::logger> logger_ =
        spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Sprites to be rendered
    std::vector<std::weak_ptr<taeto::Object>> sprites_;

    // Light sources
    std::vector<std::weak_ptr<taeto::Object>> lights_;

    // Currently loaded scene
    std::shared_ptr<Scene> scene_;

    // Engine camera
    taeto::Camera camera_ = taeto::Camera();

    // If set to true, engine will display FPS in top left corner
    bool debug_mode_on_ = true;

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

void load_light(std::weak_ptr<Light> light)
{
    logger_->debug("Adding light to engine.");
    lights_.push_back(light);
}

void load_sprite(std::weak_ptr<Sprite> sprite)
{
    logger_->debug("Adding sprite to engine.");
    sprites_.push_back(sprite);
}

void load_scene(std::shared_ptr<Scene> scene)
{
    logger_->debug("Loading scene.");
    scene_ = scene;
    scene_->load();
}

void run()
{
    if (debug_mode_on_)
        logger_->flush_on(spdlog::level::debug);
    else
        logger_->flush_on(spdlog::level::info);

    // Declare and start all systems
    logger_->info("Constructing engine systems.");
    taeto::AudioSystem audio_system_ = taeto::AudioSystem(logger_);
    // taeto::InputSystem input_system_ = taeto::InputSystem(logger_);
    taeto::RenderSystem render_system_ = taeto::RenderSystem(logger_);
    taeto::DisplaySystem display_system_ = taeto::DisplaySystem(logger_);
    taeto::PhysicsSystem physics_system_ = taeto::PhysicsSystem(logger_);
    logger_->error("Done setting up engine.");

    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int window_height_ = size.ws_row;
    int window_width_ = size.ws_col;

    // Create new frame for rendering and displaying game world
    taeto::DisplayPixelFrame frame(window_height_, window_width_);

    // Start rendering
    while (true)
    {
        // Update frame sizes if window size changed
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        int window_height_ = size.ws_row;
        int window_width_ = size.ws_col;
        frame.resize(window_height_, window_width_);

        ////////////////////////////////////////////////////////////////
        ////                       INPUT STEP                       ////
        ////////////////////////////////////////////////////////////////

        logger_->debug("Polling inputs.");
        input_system_.poll_inputs();


        ////////////////////////////////////////////////////////////////
        ////                     ANIMATION STEP                     ////
        ////////////////////////////////////////////////////////////////

        logger_->debug("Telling scene to animate.");
        // TODO

        logger_->debug("Telling sprites to animate.");
        for (std::weak_ptr<taeto::Object> current_sprite_weak_ptr : sprites_)
        {
            // Get pointer if not dead
            std::shared_ptr<taeto::Object> current_sprite;
            if (!(current_sprite = current_sprite_weak_ptr.lock()))
                continue;

            current_sprite->animate();
        }

        logger_->debug("Telling lights to animate.");
        for (std::weak_ptr<taeto::Object> current_light_weak_ptr : lights_)
        {
            // Get pointer if not dead
            std::shared_ptr<taeto::Object> current_light;
            if (!(current_light = current_light_weak_ptr.lock()))
                continue;

            // TODO
            //current_light->animate();
        }

        if (scene_)
            scene_->animate();


        ////////////////////////////////////////////////////////////////
        ////                      PHYSICS STEP                      ////
        ////////////////////////////////////////////////////////////////

        // Physics
        logger_->debug("Applying forces to sprites.");
        physics_system_.detect_collisions(sprites_);


        ////////////////////////////////////////////////////////////////
        ////                      RENDER STEP                       ////
        ////////////////////////////////////////////////////////////////

        // Clear out all dead pointers before rendering
        std::vector<std::weak_ptr<taeto::Object>>::iterator sit = sprites_.begin();
        while (sit != sprites_.end())
            if (std::shared_ptr<taeto::Object> spt = sit->lock())
                ++sit;
            else
                sit = sprites_.erase(sit);
        std::vector<std::weak_ptr<taeto::Object>>::iterator lit = lights_.begin();
        while (lit != lights_.end())
            if (std::shared_ptr<taeto::Object> lpt = lit->lock())
                ++lit;
            else
                lit = lights_.erase(lit);

        logger_->debug("Rendering new frame.");
        render_system_.render_frame(frame, camera_, sprites_, lights_);


        ////////////////////////////////////////////////////////////////
        ////                  POST-PROCESSING STEP                  ////
        ////////////////////////////////////////////////////////////////

        // Draw debug data on frame
        if (debug_mode_on_)
        {
            // Print debug information if flag is true
            frame.add_string(
                0, 0, "FPS: " + std::to_string(current_fps_));
            frame.add_string(
                1, 0, "NUM SPRITES: " + std::to_string(sprites_.size()));
            frame.add_string(
                2, 0, "NUM LIGHTS: " + std::to_string(lights_.size()));
            frame.add_string(
                3, 0,
                "CAMERA LOCATION: ("
                    + std::to_string(camera_.get_z_pixel_position()) + ", "
                    + std::to_string(camera_.get_y_pixel_position()) + ", "
                    + std::to_string(camera_.get_x_pixel_position()) + ")");
            frame.add_string(
                4, 0,
                "FRAME DIMENSIONS: "
                    + std::to_string(frame.get_height()) + "x"
                    + std::to_string(frame.get_width()));
            frame.add_string(
                5, 0, "CURRENT FRAME: " + std::to_string(frame_number_));
        }

        // Tell all sprites and scenes that a frame is about to be rendered
        logger_->debug("Posting Pre_Render_Message.");

        logger_->debug("Displaying frame.");
        display_system_.display_frame(frame);

        // Update frame rate
        int const AVERAGING_TIME = 1000;

        // Get milliseconds since epoch for saving when this frame was rendered
        std::chrono::milliseconds time =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        // Add time of this frame
        frame_times_.push_back(time);

        // Remove all values in vector that are more than 'averaging_time'
        // milliseconds old
        while (time - frame_times_.front() >
               std::chrono::milliseconds(AVERAGING_TIME))
            frame_times_.pop_front();

        frame_number_++;

        // Calculate current FPS
        current_fps_ = frame_times_.size() / (AVERAGING_TIME / 1000);
    }

    endwin();
}

void set_debug_mode(bool debug_mode_on)
{
    debug_mode_on_ = debug_mode_on;
}

}   // namespace taeto
