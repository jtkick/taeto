#ifndef ENGINE_H
#define ENGINE_H

// Systems
#include "Display_System.h"
#include "Render_System.h"

// Messages
#include "Render_Frame_Message.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"

#include "Sprite.h"
#include "Light.h"

#include <curses.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <vector>

class Engine
{
public:

    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Bus for notifying systems of messages
    shared_ptr<Message_Bus> message_bus;

    // System to render new frames
    shared_ptr<Render_System> render_system;

    // System for output to screen
    shared_ptr<Display_System> display_system;

    // Frame rate to aim for
    unsigned int target_frame_rate = 0;

    // Actual rate engine is running at
    unsigned int actual_frame_rate = 0;

    // Possibly temporary
    long long last_count_time = 0;

    // Camera position
    long int x_camera_position;
    long int y_camera_position;
    long int z_camera_position;

    // If set to true, engine will display FPS in top left corner
    bool display_frame_rate;

    public:

        Engine(void);

        ~Engine(void);

        void add_light(shared_ptr<Light>);

        void add_sprite(shared_ptr<Sprite>);

        void animate();

        void display_frame(shared_ptr<Frame>);

        // Continually render and display frames until program stopped
        void run();

};

#endif
