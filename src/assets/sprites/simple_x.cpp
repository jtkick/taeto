#include "assets/sprites/simple_x.hpp"

#include <memory>

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "object/position.hpp"

namespace taeto
{

SimpleX::SimpleX()
{
    pixel_ = taeto::RenderPixel(
        'X',
        taeto::Color(255, 0, 0, 255),
        taeto::Color(0, 255, 0, 255),
        false
    );
}

const taeto::RenderPixel& SimpleX::get_pixel_at(
    uint64_t h, uint64_t w)
{
    return pixel_;
}

uint64_t SimpleX::height()
{
    return 10;
}

uint64_t SimpleX::width()
{
    return 20;
}

bool SimpleX::respect_light_sources()
{
    return true;
}

}   // namespace taeto
