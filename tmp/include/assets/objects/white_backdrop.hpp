#ifndef ASSETS_OBJECTS_WHITE_BACKDROP_HPP_
#define ASSETS_OBJECTS_WHITE_BACKDROP_HPP_

#include "frames/render_pixel_frame.h"
#include "object/object.hpp"

namespace taeto
{

class WhiteBackdrop: public Object, public IRenderable
{
public:
    WhiteBackdrop();

private:
    taeto::RenderPixelFrame frame_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_WHITE_BACKDROP_HPP_
