#ifndef SYSTEMS_RENDER_SYSTEM_HPP_
#define SYSTEMS_RENDER_SYSTEM_HPP_

#include <chrono>
#include <deque>
#include <memory>
#include <tuple>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/camera.hpp"
#include "components/display_pixel.hpp"
#include "components/render_pixel.hpp"
#include "frames/display_pixel_frame.hpp"
#include "object/object.hpp"
#include "systems/system.hpp"

namespace taeto
{

class RenderSystem : public System
{
public:
    RenderSystem();

    RenderSystem(std::shared_ptr<spdlog::logger>);

    ~RenderSystem();

    /**
     * Render a PixelFrame with all known objects in the engine. Uses a
     * ray-casting type method and deferred lighting.
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame(
        taeto::DisplayPixelFrame&,
        taeto::Camera&,
        std::vector<std::weak_ptr<taeto::Object>>& sprites,
        std::vector<std::weak_ptr<taeto::Object>>& lights
    );

    /**
     * Render a PixelFrame with all known objects in the engine. Draws sprites
     * one at a time.
     * CURRENTLY A WORK IN PROGRESS, HAS WEIRD ARTIFACTS AND PROBABLY CRASHES
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame_by_drawing(
        taeto::DisplayPixelFrame&,
        std::vector<std::weak_ptr<taeto::Object>>& sprites,
        std::vector<std::weak_ptr<taeto::Object>>& lights
    );

private:
    // First rendered frame: pixels before lighting applied with additional data
    // typedef std::vector<std::vector<std::vector<std::tuple<
    //     taeto::DisplayPixel, taeto::Position>>>> AlbedoFrame;

    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger_;

    // Currently loaded skybox
    // taeto::Skybox skybox_;

    // Number of tiles away from camera that sprites will be rendered
    unsigned int render_distance_;

    // Number of sprites rendered in the last frame
    unsigned int drawn_sprites_;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_HPP_
