#ifndef ASSETS_SPRITES_ROFLCOPTER_HPP_
#define ASSETS_SPRITES_ROFLCOPTER_HPP_

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/isprite.hpp"

namespace taeto
{

class Roflcopter: public ISprite
{
public:
    Roflcopter(glm::uvec2 s, taeto::RenderPixel p);

    taeto::RenderPixel pixel_at(glm::uvec2& pos);

private:
    glm::uvec2 shape_;
    taeto::RenderPixel pixel_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_ROFLCOPTER_HPP_
