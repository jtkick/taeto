#include "taeto/objects/sprites/rectangle.hpp"

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

Rectangle::Rectangle(glm::uvec2 s, taeto::RenderPixel p)
{
    shape(s);
    shape_ = s;
    pixel_ = p;
}

taeto::RenderPixel Rectangle::pixel_at(const glm::uvec2& pos)
{  
    (void) pos;
    return pixel_;
}

}   // namespace taeto
