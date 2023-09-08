#include "assets/objects/white_backdrop.hpp"

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.h"

namespace taeto
{

WhiteBackdrop::WhiteBackdrop()
{
    // Default position to the origin
    x_position_ = -100;
    y_position_ = -50;
    z_position_ = 0;

    respect_light_sources = true;

    taeto::RenderPixel p =
        taeto::RenderPixel(' ', taeto::Color(), taeto::Color(255, 255, 255), false);
    frame_ = taeto::RenderPixelFrame(65, 200, p);
}

taeto::RenderPixel WhiteBackdrop::get_pixel_at(uint64_t y, uint64_t x)
{
    return frame_.at(y, x);
}

uint64_t WhiteBackdrop::height()
{
    return frame_.height();
}

uint64_t WhiteBackdrop::width()
{
    return frame_.width();
}

WhiteBackdrop::plane_orientation()
{
    return 'Z';
}

}
