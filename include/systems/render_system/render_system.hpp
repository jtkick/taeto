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
#include "object/light.hpp"
#include "object/sprite.hpp"
#include "systems/system.hpp"

namespace taeto
{

class RenderSystem : public System
{
public:
    RenderSystem() : render_distance_(1000000000) { };

    ~RenderSystem() { };

    /**
     * Render a PixelFrame with all known objects in the engine. Uses a
     * ray-casting type method and deferred lighting.
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame(
        taeto::DisplayPixelFrame&,
        taeto::Camera&,
        std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
        std::vector<std::weak_ptr<taeto::Light>>& lights
    ) { throw std::runtime_error("bro"); };

protected:
    // First rendered frame: pixels before lighting applied with additional data
    // typedef std::vector<std::vector<std::vector<std::tuple<
    //     taeto::DisplayPixel, taeto::Position>>>> AlbedoFrame;

    // Currently loaded skybox
    // taeto::Skybox skybox_;

    // Number of tiles away from camera that sprites will be rendered
    unsigned int render_distance_;

    // Number of sprites rendered in the last frame
    unsigned int drawn_sprites_;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_HPP_
