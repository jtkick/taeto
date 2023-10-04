#ifndef SYSTEMS_RENDER_SYSTEM_DRAWING_RENDER_SYSTEM_HPP_
#define SYSTEMS_RENDER_SYSTEM_DRAWING_RENDER_SYSTEM_HPP_

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/camera.hpp"
#include "components/render_pixel.hpp"
#include "frames/display_pixel_frame.hpp"
#include "object/light.hpp"
#include "object/sprite.hpp"
#include "systems/render_system/render_system.hpp"

namespace taeto
{

class DrawingRenderSystem : public RenderSystem
{
public:
    DrawingRenderSystem();

    DrawingRenderSystem(std::shared_ptr<spdlog::logger>);

    ~DrawingRenderSystem();

    /**
     * Render a PixelFrame with all known objects in the engine. Uses a
     * ray-casting type method and deferred lighting.
     *
     * @param rendered_frame Frame to write rendered pixels to.
    */
    void render_frame(
        taeto::DisplayPixelFrame&,
        taeto::Camera&,
        std::vector<std::weak_ptr<taeto::Sprite>>&,
        std::vector<std::weak_ptr<taeto::Light>>&
    );
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_DRAWING_RENDER_SYSTEM_HPP_