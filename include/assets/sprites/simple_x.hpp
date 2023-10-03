#ifndef ASSETS_SPRITES_SIMPLE_X_H_
#define ASSETS_SPRITES_SIMPLE_X_H_

#include <memory>

#include "components/render_pixel.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class SimpleX: public taeto::Sprite
{
public:
    SimpleX();

    const taeto::RenderPixel& get_pixel_at(uint64_t, uint64_t) override;

    bool respect_light_sources();

    uint64_t height() override;

    uint64_t width() override;

private:
    taeto::RenderPixel pixel_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_SIMPLE_X_H_
