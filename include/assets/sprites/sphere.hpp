#ifndef ASSETS_SPRITES_SPHERE_H_
#define ASSETS_SPRITES_SPHERE_H_

#include <memory>

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class Sphere: public taeto::Sprite
{
public:
    Sphere(int);

    const taeto::RenderPixel& get_pixel_at(uint64_t, uint64_t) override;

    uint64_t height() override;
    uint64_t width() override;

    bool respect_light_sources() override;

private:
    taeto::RenderPixelFrame frame_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_SPHERE_H_
