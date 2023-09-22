#include "assets/objects/checkerboard.hpp"

#include "components/color.hpp"
#include "components/render_pixel.hpp"

namespace taeto
{

Checkerboard::Checkerboard(uint64_t h, uint64_t w, taeto::Color c, char o = 'Z')
{
    height_ = h;
    width_ = w;

    plane_orientation_ = o;

    taeto::Color light_color_ = c;
    taeto::Color dark_color_ = taeto::Color(c.red/2, c.green/2, c.blue/2, 255);
}

taeto::RenderPixel Checkerboard::get_pixel_at(
    unsigned long int y, unsigned long int x)
{
    // Pixel to return
    taeto::RenderPixel p;

    // Set background color to alternate in checkerboard pattern
    p.background_color = (x%8<4)!=(y%4<2) ? light_color_ : dark_color_;

    return p;
}

}   // namespace taeto
