#include "taeto/objects/sprites/checkerboard.hpp"

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

Checkerboard::Checkerboard(glm::uvec2 s, glm::vec3 c, bool respect_light_sources)
{
    shape_ = s;

    respect_light_sources_ = respect_light_sources;

    light_color_ = glm::vec4(c, 1.0);
    dark_color_ = glm::vec4{c*0.75f, 1.0};
}

taeto::RenderPixel Checkerboard::get_pixel_at(glm::uvec2 pos)
{
    // Pixel to return
    taeto::RenderPixel p;

    // Set background color to alternate in checkerboard pattern
    p.bg_color = (pos.x % 8 < 4)!=(pos.y % 4 < 2) ? light_color_ : dark_color_;

    return p;
}

}   // namespace taeto
