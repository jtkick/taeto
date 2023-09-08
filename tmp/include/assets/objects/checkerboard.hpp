#ifndef ASSETS_OBJECTS_CHECKERBOARD_H_
#define ASSETS_OBJECTS_CHECKERBOARD_H_

#include "components/color.hpp"
#include "object/object.hpp"
#include "object/i_renderable.hpp"

namespace taeto
{

class Checkerboard: public Object, public IRenderable
{
public:
    Checkerboard();

    Checkerboard(uint64_t, uint64_t, taeto::Color, char);

    taeto::RenderPixel get_pixel_at(unsigned long int, unsigned long int);

    unsigned long int height();

    char plane_orientation();

    unsigned long int width();

private:
    unsigned long int height_;
    unsigned long int width_;
    char plane_orientation_;
    taeto::Color light_color_;
    taeto::Color dark_color_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_CHECKERBOARD_H_
