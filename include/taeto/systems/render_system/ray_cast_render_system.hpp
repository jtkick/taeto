#ifndef SYSTEMS_RENDER_SYSTEM_RAY_CAST_RENDER_SYSTEM_HPP_
#define SYSTEMS_RENDER_SYSTEM_RAY_CAST_RENDER_SYSTEM_HPP_

#include <memory>
#include <vector>

#include "taeto/objects/camera.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/objects/lights/light.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/systems/render_system/render_system.hpp"

namespace taeto
{

class RayCastRenderSystem : public RenderSystem
{
public:
    RayCastRenderSystem() { hdr_ = true; bloom_ = true; render_normals_ = false;};

    ~RayCastRenderSystem() { };

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

#endif  // SYSTEMS_RENDER_SYSTEM_RAY_CAST_RENDER_SYSTEM_HPP_
