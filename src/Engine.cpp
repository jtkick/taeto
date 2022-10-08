#include "Engine.h"

// For getting window size info in UNIX
#include <sys/ioctl.h>
#include <unistd.h>

// Used for scaling angle from between 0 and pi, to between 0 and 255
#define ANGLE_SCALE (255/3.14159265)

Engine::Engine()
{
    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    window_height = size.ws_row;
    window_width = size.ws_col;

    // Create engine-wide logger
    logger = spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Make sure logger flushes on all error messages
    logger->flush_on(spdlog::level::info);

    // Create message bus
    logger->info("Constructing message bus.");
    message_bus = make_shared<Message_Bus>(logger);
    // message_bus = Message_Bus(logger);

    // Setup all engine systems
    logger->info("Constructing engine systems.");
    audio_system = Audio_System(logger, message_bus);
    input_system = Input_System(logger, message_bus);
    render_system = Render_System(logger, message_bus);
    display_system = Display_System(logger, message_bus);
    physics_system = Physics_System(logger, message_bus);
    // audio_system = make_shared<Audio_System>(logger, message_bus);
    // input_system = make_shared<Input_System>(logger, message_bus);
    // render_system = make_shared<Render_System>(logger, message_bus);
    // display_system = make_shared<Display_System>(logger, message_bus);
    // physics_system = make_shared<Physics_System>(logger, message_bus);

    // Connect systems to message bus
    logger->info("Conencting systems to message bus.");
    message_bus->add_system(std::make_shared<Audio_System>(audio_system));
    message_bus->add_system(std::make_shared<Input_System>(input_system));
    message_bus->add_system(std::make_shared<Render_System>(render_system));
    message_bus->add_system(std::make_shared<Display_System>(display_system));
    message_bus->add_system(std::make_shared<Physics_System>(physics_system));

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
    s->load(window_height, window_width);
}

void Engine::run()
{
    // Create new frame

    shared_ptr<Frame> frame = make_shared<Frame>(window_height, window_width);

    //sf::Music m;

    std::shared_ptr<Frame> f = make_shared<Frame>(3, 6);
    Color w = Color(255, 255, 255);
    Color g = Color(43, 43, 43);
    Color a = Color(255, 255, 255, 0);
    f->set_chars({ R"(@@__@@)",
                  R"(@( ')')",
                  R"(@@@@@@)",});
    f->set_foreground_colors( { { a, a, g, g, a, a },
                               { a, g, g, g, g, g },
                               { a, a, a, a, a, a } } );
    f->set_background_colors( { { w, w, a, a, w, w },
                               { w, w, w, w, w, w },
                               { w, w, w, w, w, w } } );


    // Start rendering
    while (true)
    {
        logger->info("Polling inputs.");
        shared_ptr<Poll_Inputs_Message> pim = make_shared<Poll_Inputs_Message>();
        message_bus->post_message(pim);

        logger->info("Telling scenes to animate.");
        shared_ptr<Animate_Message> am = make_shared<Animate_Message>();
        message_bus->post_message(am);

        logger->info("Applying forces to sprites.");
        shared_ptr<Apply_Forces_Message> afm = make_shared<Apply_Forces_Message>();
        message_bus->post_message(afm);

        logger->info("Rendering new frame.");
        shared_ptr<Render_Frame_Message> rfm = make_shared<Render_Frame_Message>(frame);
        message_bus->post_message(rfm);

        // Tell all sprites and scenes that a frame is about to be rendered
        logger->info("Posting Pre_Render_Message.");
        shared_ptr<Pre_Render_Message> prm = make_shared<Pre_Render_Message>();
        message_bus->post_message(prm);

        logger->info("Displaying frame.");
        shared_ptr<Display_Frame_Message> dfm = make_shared<Display_Frame_Message>(frame);
        message_bus->post_message(dfm);
    }
}
