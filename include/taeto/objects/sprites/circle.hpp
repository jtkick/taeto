#ifndef ASSETS_SPRITES_CIRCLE_H_
#define ASSETS_SPRITES_CIRCLE_H_

#include <memory>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/objects/isprite.hpp"
#include "taeto/objects/sprites/sprite.hpp"

namespace taeto
{

class Circle: public ISprite
{
public:
    Circle(
        int diameter,
        taeto::RenderPixel r = taeto::RenderPixel(),
        bool spherical_normals = false);

    taeto::RenderPixel pixel_at(const glm::uvec2& pos);

private:
    taeto::RenderPixelFrame frame_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_CIRCLE_H_
