#ifndef ASSETS_SPRITES_ROFLCOPTER_HPP_
#define ASSETS_SPRITES_ROFLCOPTER_HPP_

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class Roflcopter: public taeto::Sprite
{
public:
    Roflcopter(glm::uvec2 s, taeto::RenderPixel p);

    taeto::RenderPixel get_pixel_at(glm::uvec2 pos);

private:
    taeto::RenderPixel pixel_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_ROFLCOPTER_HPP_
