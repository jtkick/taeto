#ifndef ASSETS_SPRITES_SIMPLE_X_H_
#define ASSETS_SPRITES_SIMPLE_X_H_

#include <memory>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/sprites/sprite.hpp"

namespace taeto
{

class SimpleX: public taeto::Sprite
{
public:
    SimpleX();

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

    bool respect_light_sources();

    uint height() override;

    uint width() override;

private:
    taeto::RenderPixel pixel_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_SIMPLE_X_H_
