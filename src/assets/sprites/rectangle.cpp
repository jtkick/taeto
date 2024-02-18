#include "assets/sprites/rectangle.hpp"

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"

namespace taeto
{

Rectangle::Rectangle(glm::uvec2 s, taeto::RenderPixel p)
{
    shape_ = s;
    pixel_ = p;
}

taeto::RenderPixel Rectangle::get_pixel_at(glm::uvec2 pos)
{
    return pixel_;
}

}   // namespace taeto
