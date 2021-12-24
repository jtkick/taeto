#ifndef ENGINE_H
#define ENGINE_H

// Systems
#include "Audio_System.h"
#include "Input_System.h"
#include "Display_System.h"
#include "Render_System.h"
#include "Physics_System.h"

// Scene layer
#include "Scene.h"

// Messages
#include "Animate_Message.h"
#include "Apply_Forces_Message.h"
#include "Poll_Inputs_Message.h"
#include "Pre_Render_Message.h"
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
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Bus for notifying systems of messages
    shared_ptr<Message_Bus> message_bus;

    // System to play sounds and music
    shared_ptr<Audio_System> audio_system;

    // System to poll any inputs
    shared_ptr<Input_System> input_system;

    // System to render new frames
    shared_ptr<Render_System> render_system;

    // System for output to screen
    shared_ptr<Display_System> display_system;

    // System for applying physics and detecting collisions
    shared_ptr<Physics_System> physics_system;

    // Currently loaded scenes
    vector<shared_ptr<Scene>> scenes;

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

    // Distance to drawing plane with respect to camera's z location
    unsigned int drawing_plane_distance;

    // If set to true, engine will display FPS in top left corner
    bool display_frame_rate;

    // Keep screen size
    int window_height;
    int window_width;

    public:

        Engine(void);

        ~Engine(void);

        void add_light(shared_ptr<Light>);

        void add_sprite(shared_ptr<Sprite>);

        void load_scene(shared_ptr<Scene>);

        // Continually render and display frames until program stopped
        void run();

};

#endif
