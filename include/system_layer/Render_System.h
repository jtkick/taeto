#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Message.h"
#include "Render_Frame_Message.h"
#include "Sprite_Update_Message.h"
#include "System.h"
#include "Sprite.h"
#include "Light.h"

#include <chrono>
#include <deque>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <vector>



#include <iostream>

using namespace std;
using namespace std::chrono;

class Render_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Sprites to be rendered
    vector<shared_ptr<Sprite>> sprites;

    // Light sources
    vector<shared_ptr<Light>> lights;

    // Current frame rate of render system
    // List of times each frame was rendered
    std::deque<milliseconds> frame_times;

    // Amount of time in milliseconds to average in order to determine FPS
    unsigned int averaging_time = 2000;

    // Member to store current FPS
    unsigned int current_fps;

    // Camera position
    long int camera_x_position;
    long int camera_y_position;
    long int camera_z_position;

    // Distance of drawing frame from camera
    unsigned int drawing_plane_distance;

    // Number of tiles away from camera that sprites will be rendered
    unsigned int render_distance;

    // If set to true, engine information is added to top-left of frame
    bool display_debug_info;

    // Number of sprites rendered in the last frame
    unsigned int drawn_sprites;

    public:

        // Contructor
        Render_System();

        Render_System(shared_ptr<spdlog::logger>);

        // Destructor
        ~Render_System(void);

        // Read messages from message bus
        void handle_message(shared_ptr<Message>);

    // These methods are for doing work in this system
    // They are private since all calls to do work should be done
    // using the message bus
    private:

        // Move camera to specified location
        void move_camera(long int, long int, long int);

        // Used to render new frame
        void render_frame(shared_ptr<Frame>);

};

#endif
