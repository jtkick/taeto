#ifndef ENGINE_H
#define ENGINE_H

#include "Display_System.h"
#include "Render_System.h"
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

    // System to render new frames
    Render_System render_system;

    // System for output to screen
    Display_System display_system;

    // Sprites to render
    vector<Sprite*> sprites;

    // Light sources
    vector<Light*> lights;

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

};

#endif
