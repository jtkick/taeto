#include "Engine.h"

// For getting window size info in UNIX
#include <sys/ioctl.h>
#include <unistd.h>

// Used for scaling angle from between 0 and pi, to between 0 and 255
#define ANGLE_SCALE (255/3.14159265)

Engine::Engine()
{
    logger = spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Make sure logger flushes on all error messages
    logger->flush_on(spdlog::level::err);

    // Setup all engine systems
    logger->info("Setting up engine systems.");
    render_system = make_shared<Render_System>(logger, message_bus);
    display_system = make_shared<Display_System>(logger, message_bus);

    // Connect systems to message bus
    message_bus->add_system(render_system);
    message_bus->add_system(display_system);

    logger->error("Done setting up engine.");
}

Engine::~Engine()
{
    endwin();
}

void Engine::add_light(shared_ptr<Light> l)
{
    logger->error("Adding light to engine.");

    // Create message
    shared_ptr<Light_Update_Message> lum = make_shared<Light_Update_Message>(l);

    // Post message
    render_system->handle_message(lum);
}

void Engine::add_sprite(shared_ptr<Sprite> s)
{
    logger->error("Adding sprite to engine.");

    // Create sprite update message
    shared_ptr<Sprite_Update_Message> sum = make_shared<Sprite_Update_Message>(s, true, true);

    // Post message
    render_system->handle_message(sum);
}

void Engine::run()
{
    // Create new frame
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    shared_ptr<Frame> frame = make_shared<Frame>(size.ws_row, size.ws_col);

    // Start rendering
    while (true)
    {
        logger->info("Rendering new frame.");
        shared_ptr<Render_Frame_Message> rfm = make_shared<Render_Frame_Message>(frame);
        render_system->handle_message(rfm);

        logger->info("Displaying frame.");
        shared_ptr<Display_Frame_Message> dfm = make_shared<Display_Frame_Message>(frame);
        display_system->handle_message(dfm);
    }
}
