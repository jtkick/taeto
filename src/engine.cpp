#include "engine.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "components/light.h"
#include "components/sprite.h"
#include "scenes/scene.hpp"
#include "systems/audio_system.hpp"
#include "systems/input_system.hpp"
#include "systems/display_system.hpp"
#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"

namespace taeto
{

Engine::Engine()
{
    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    window_height_ = size.ws_row;
    window_width_ = size.ws_col;

    // Create engine-wide logger
    logger_ = spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Make sure logger flushes on all error messages
    logger_->flush_on(spdlog::level::info);

    // Setup all engine systems
    logger_->info("Constructing engine systems.");
    audio_system_ = taeto::AudioSystem(logger_);
    input_system_ = taeto::InputSystem(logger_);
    render_system_ = taeto::RenderSystem(logger_);
    display_system_ = taeto::DisplaySystem(logger_);
    physics_system_ = taeto::PhysicsSystem(logger_);

    logger_->error("Done setting up engine.");
}

Engine::~Engine()
{
    endwin();
}

void Engine::add_light(shared_ptr<Light> l)
{
    logger_->error("Adding light to engine.");
    throw "not implemented";
}

void Engine::add_sprite(shared_ptr<Sprite> s)
{
    logger_->error("Adding sprite to engine.");
    throw "not implemented";
}

void Engine::load_scene(shared_ptr<Scene> s)
{
    logger_->info("Adding scene to engine.");

    // Save state

    // Unload old scene and assets

    // Load new scene

    throw "not implemented";
    // s->load(window_height_, window_width_);
}

void Engine::run()
{
    // Create new frame for rendering and displaying game world
    shared_ptr<Frame> frame = make_shared<Frame>(window_height_, window_width_);

    // Start rendering
    while (true)
    {
        logger_->info("Polling inputs.");
        input_system_.poll_inputs();

        logger_->info("Applying forces to sprites.");

        logger_->info("Telling scenes to animate.");

        logger_->info("Rendering new frame.");
        render_system_.render_frame(frame);

        // Tell all sprites and scenes that a frame is about to be rendered
        logger_->info("Posting Pre_Render_Message.");

        logger_->info("Displaying frame.");
        display_system_.display_frame(frame);
    }
}

}   // namespace taeto
