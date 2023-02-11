#ifndef ASSETS_OBJECTS_STATIONARY_BOX_H_
#define ASSETS_OBJECTS_STATIONARY_BOX_H_

#include "components/sprite.h"

namespace taeto
{

class StationaryBox: public taeto::Sprite
{
public:
    StationaryBox();

    void set_color(taeto::Color);
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_STATIONARY_BOX_H_
