#ifndef ASSETS_OBJECTS_LIGHT_FILTER_H_
#define ASSETS_OBJECTS_LIGHT_FILTER_H_

#include "components/color.h"
#include "components/sprite.h"

namespace taeto
{

class LightFilter: public Sprite
{
public:
    LightFilter(Color);
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_LIGHT_FILTER_H_
