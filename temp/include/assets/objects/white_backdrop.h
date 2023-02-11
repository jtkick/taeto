#ifndef ASSETS_OBJECTS_WHITE_BACKDROP_H_
#define ASSETS_OBJECTS_WHITE_BACKDROP_H_

#include "components/frame.h"
#include "components/sprite.h"

namespace taeto
{

class WhiteBackdrop: public Sprite
{
public:
    WhiteBackdrop();

private:
    taeto::Frame default_frame_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_WHITE_BACKDROP_H_
