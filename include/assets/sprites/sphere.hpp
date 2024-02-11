#ifndef ASSETS_SPRITES_SPHERE_H_
#define ASSETS_SPRITES_SPHERE_H_

#include <memory>

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class Sphere: public taeto::Sprite
{
public:
    Sphere(int);

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

    uint height() override;
    uint width() override;

    bool respect_light_sources() override;

private:
    taeto::RenderPixelFrame frame_;
};

}   // namespace taeto

#endif  // ASSETS_SPRITES_SPHERE_H_
