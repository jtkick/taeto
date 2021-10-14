#include "Engine.h"

// For getting window size info in UNIX
#include <sys/ioctl.h>
#include <unistd.h>

// Used for scaling angle from between 0 and pi, to between 0 and 255
#define ANGLE_SCALE (255/3.14159265)

Engine::Engine()
{
    // Create engine-wide logger
    logger = spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Make sure logger flushes on all error messages
    logger->flush_on(spdlog::level::err);

    // Create message bus
    logger->info("Constructing message bus.");
    message_bus = make_shared<Message_Bus>(logger);

    // Setup all engine systems
    logger->info("Constructing engine systems.");
    input_system = make_shared<Input_System>(logger, message_bus);
    render_system = make_shared<Render_System>(logger, message_bus);
    display_system = make_shared<Display_System>(logger, message_bus);
    physics_system = make_shared<Physics_System>(logger, message_bus);

    // Connect systems to message bus
    logger->info("Conencting systems to message bus.");
    message_bus->add_system(input_system);
    message_bus->add_system(render_system);
    message_bus->add_system(display_system);
    message_bus->add_system(physics_system);

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
    message_bus->post_message(lum);
}

void Engine::add_sprite(shared_ptr<Sprite> s)
{
    logger->error("Adding sprite to engine.");

    // Create sprite update message
    shared_ptr<Sprite_Update_Message> sum = make_shared<Sprite_Update_Message>(s);

    // Post message
    message_bus->post_message(sum);
}

void Engine::load_scene(shared_ptr<Scene> s)
{
    logger->info("Adding scene to engine.");

    // Connect engine to scene
    scenes.push_back(s);
    message_bus->add_system(s);

    // Connect scene to engine
    s->connect_to_bus(message_bus);
    s->connect_to_logger(logger);

    // Now that scene is setup correctly, tell it to load all assets
    s->load();
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
        logger->info("Polling inputs.");
        shared_ptr<Poll_Inputs_Message> pim = make_shared<Poll_Inputs_Message>();
        message_bus->post_message(pim);

        logger->info("Applying forces to sprites.");
        shared_ptr<Apply_Forces_Message> afm = make_shared<Apply_Forces_Message>();
        message_bus->post_message(afm);

        logger->info("Rendering new frame.");
        shared_ptr<Render_Frame_Message> rfm = make_shared<Render_Frame_Message>(frame);
        message_bus->post_message(rfm);

        logger->info("Displaying frame.");
        shared_ptr<Display_Frame_Message> dfm = make_shared<Display_Frame_Message>(frame);
        message_bus->post_message(dfm);
    }

    static unsigned int frames;

    // Keep track of number of frames until second elapses
    long long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    if (now - last_count_time > 1000)
    {
        actual_frame_rate = frames;
        frames = 0;

        // Last run time
        last_count_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    }

    rendered_frame->add_string(1, 0, "FPS: " + std::to_string(actual_frame_rate));
    rendered_frame->add_string(2, 0, "CURRENT DIMENSIONS: " + std::to_string(rendered_frame->get_width())
                                     + "x" + std::to_string(rendered_frame->get_height()));
    rendered_frame->add_string(3, 0, "NUM SPRITES: " + std::to_string(sprites.size()));
    rendered_frame->add_string(4, 0, "NUM LIGHTS: " + std::to_string(lights.size()));
    rendered_frame->add_string(5, 0, "CAMERA LOCATION: (" + std::to_string(x_camera_position) + ", "
                                                          + std::to_string(y_camera_position) + ", "
                                                          + std::to_string(z_camera_position) + ")");
    rendered_frame->add_string(6, 0, "WILL TO LIVE: " + std::to_string(0));


    frames++;

    return;

}
