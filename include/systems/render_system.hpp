#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <chrono>
#include <deque>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "systems/system.h"
#include "components/sprite.h"
#include "components/light.h"

namespace taeto
{

class RenderSystem: public System
{
public:
    RenderSystem();

    RenderSystem(std::shared_ptr<spdlog::logger>);

    ~RenderSystem();

    // Move camera to specified location
    void move_camera(long int, long int, long int);

    // Used to render new frame
    void render_frame(Frame&);

    // Render frame by drawing each sprite instead of ray casting (work in progress)
    void render_frame_by_drawing(std::shared_ptr<Frame>);

    // Update current FPS
    void update_fps();

    // Write alternating white and grey pattern to frame
    void write_alpha_background(std::shared_ptr<Frame>);

    // Write old-school tv test screen bars to frame
    void write_color_bars(std::shared_ptr<Frame>);

    // Write info for debugging to frame after rendering
    void write_debug_info(std::shared_ptr<Frame>);

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    std::shared_ptr<Message_Bus> message_bus;

    // Sprites to be rendered
    std::vector<std::shared_ptr<taeto::Sprite>> sprites;

    // Light sources
    std::vector<std::shared_ptr<taeto::Light>> lights;

    // Current frame rate of render system
    // List of times each frame was rendered
    std::deque<std::chrono::milliseconds> frame_times;

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
};

}   // namespace taeto

#endif
