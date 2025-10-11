#ifndef ASSETS_SPRITES_RECTANGLE_HPP_
#define ASSETS_SPRITES_RECTANGLE_HPP_

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/isprite.hpp"

namespace taeto
{

class Rectangle: public ISprite
{
public:
    Rectangle(glm::uvec2 s, taeto::RenderPixel p = taeto::RenderPixel(
        ' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));

    taeto::RenderPixel pixel_at(const glm::uvec2& pos);

    // glm::uvec2& shape() { return shape_; };

private:
    taeto::RenderPixel pixel_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_RECTANGLE_HPP_
