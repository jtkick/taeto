#ifndef SYSTEMS_RENDER_SYSTEM_H_
#define SYSTEMS_RENDER_SYSTEM_H_

#include <chrono>
#include <deque>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "systems/system.hpp"
#include "components/sprite.h"
#include "components/light.h"

namespace taeto
{

class RenderSystem : public System
{
public:
    RenderSystem();

    RenderSystem(std::shared_ptr<spdlog::logger>);

    ~RenderSystem();

    /**
     * Move the camera to the given location in the game world.
     *
     * @param camera_z_position The camera's location on the z-axis.
     * @param camera_y_position The camera's location on the y-axis.
     * @param camera_x_position The camera's location on the x-axis.
     */
    void move_camera(long int, long int, long int);

    /**
     * Render a PixelFrame with all known objects in the engine. Uses a ray-casting type method and deferred lighting.
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame(taeto::Frame&);

    /**
     * Render a PixelFrame with all known objects in the engine. Draws sprites one at a time.
     * CURRENTLY A WORK IN PROGRESS, HAS WEIRD ARTIFACTS AND PROBABLY CRASHES
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame_by_drawing(taeto::Frame&);

    /**
     * Caclculates the current frames-per-second of the Rendering System.
     */
    void update_fps();

    /**
     * Writes debugging information to the rendered frame in the top-left corner.
     *
     * @param rendered_frame Frame to write the information to.
     */
    void write_debug_info(taeto::Frame&);

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger_;

    // Currently loaded skybox
    // taeto::Skybox skybox_;

    // Sprites to be rendered
    std::vector<std::shared_ptr<taeto::Sprite>> sprites_;

    // Light sources
    std::vector<std::shared_ptr<taeto::Light>> lights_;

    // Camera position
    long int camera_x_position_;
    long int camera_y_position_;
    long int camera_z_position_;

    // Distance of drawing frame from camera
    unsigned int focal_length_;

    // Number of tiles away from camera that sprites will be rendered
    unsigned int render_distance_;

    // If set to true, engine information is added to top-left of frame
    bool display_debug_info_;

    // Number of sprites rendered in the last frame
    unsigned int drawn_sprites_;

    // Keep track of frame number for debugging
    unsigned long long frame_number_;

    // Current frames-per-second
    std::deque<std::chrono::milliseconds> frame_times_;
    unsigned long current_fps_;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_H_
