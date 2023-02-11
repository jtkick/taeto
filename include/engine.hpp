#ifndef ENGINE_H_
#define ENGINE_H_

#include <curses.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/light.h"
#include "components/sprite.h"
#include "scenes/scene.hpp"
#include "systems/audio_system.hpp"
#include "systems/input_system.hpp"
#include "systems/display_system.hpp"
#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"

namespace taeto {

class Engine
{
public:
    Engine();

    ~Engine();

    void add_light(std::shared_ptr<Light>);

    void add_sprite(std::shared_ptr<Sprite>);

    void load_scene(std::shared_ptr<Scene>);

    // Continually render and display frames until program stopped
    void run();

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger_;

    // System to play sounds and music
    taeto::AudioSystem audio_system_;

    // System to poll any inputs
    taeto::InputSystem input_system_;

    // System to render new frames
    taeto::RenderSystem render_system_;

    // System for output to screen
    taeto::DisplaySystem display_system_;

    // System for applying physics and detecting collisions
    taeto::PhysicsSystem physics_system_;

    // Currently loaded scenes
    std::vector<std::shared_ptr<Scene>> scenes_;

    // Frame rate to aim for
    unsigned int target_frame_rate_ = 0;

    // Actual rate engine is running at
    unsigned int actual_frame_rate_ = 0;

    // Possibly temporary
    long long last_count_time_ = 0;

    // Camera position
    long int x_camera_position_;
    long int y_camera_position_;
    long int z_camera_position_;

    // Distance to drawing plane with respect to camera's z location
    unsigned int drawing_plane_distance_;

    // If set to true, engine will display FPS in top left corner
    bool display_frame_rate_;

    // Keep screen size
    int window_height_;
    int window_width_;
};

}   // namespace taeto

#endif  // ENGINE_H_
