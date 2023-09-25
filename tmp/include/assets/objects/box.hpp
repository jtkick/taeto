#ifndef ASSETS_OBJECTS_BOX_H_
#define ASSETS_OBJECTS_BOX_H_

#include "components/color.hpp"
#include "object/sprite.hpp"

namespace taeto
{

class Box: public taeto::Sprite
{
public:
    Box();

    Box(
        unsigned int height,
        unsigned int width,
        taeto::Color color(255, 255, 255, 255)) :
        height_(height),
        width_(width),
        color_(color);

    const taeto::RenderPixel& get_pixel_at(uint64_t, uint64_t);

private:
    taeto::Color color_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_BOX_H_
