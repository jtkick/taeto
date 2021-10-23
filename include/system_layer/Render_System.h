#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Message.h"
#include "Message_Bus.h"
#include "Render_Frame_Message.h"
#include "Key_Update_Message.h"
#include "Light_Update_Message.h"
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

using namespace std;
using namespace std::chrono;

class Render_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    // Sprites to be rendered
    vector<shared_ptr<Sprite>> sprites;

    // Light sources
    vector<shared_ptr<Light>> lights;

    // Current frame rate of render system
    // List of times each frame was rendered
    std::deque<milliseconds> frame_times;

    // Amount of time in milliseconds to average in order to determine FPS
    unsigned int averaging_time = 1000;

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

    // Keep track of frame number for debugging
    unsigned long long frame_number;

    public:

        // Contructor
        Render_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

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

        // Old way of doing it for testing
        void render_frame_old(shared_ptr<Frame>);

        // Update current FPS
        void update_fps();

        // Write alternating white and grey pattern to frame
        void write_alpha_background(shared_ptr<Frame>);

        // Write old-school tv test screen bars to frame
        void write_color_bars(shared_ptr<Frame>);

        // Write info for debugging to frame after rendering
        void write_debug_info(shared_ptr<Frame>);
};

#endif
