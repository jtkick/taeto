#ifndef ASSETS_OBJECTS_CHECKERBOARD_HPP_
#define ASSETS_OBJECTS_CHECKERBOARD_HPP_

#include "components/color.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class Checkerboard: public taeto::Sprite
{
public:
    Checkerboard() :
        height_(0),
        width_(0),
        light_color_(taeto::Color(255, 255, 255, 255)),
        dark_color_(taeto::Color(127, 127, 127, 255)),
        plane_orientation_('Z') { }

    Checkerboard(uint64_t, uint64_t, taeto::Color, char);

    taeto::RenderPixel get_pixel_at(uint64_t, uint64_t);

private:
    taeto::Color light_color_;
    taeto::Color dark_color_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_CHECKERBOARD_H_
