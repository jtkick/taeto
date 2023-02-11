#ifndef ASSETS_LIGHTS_SPOTLIGHT_H
#define ASSETS_LIGHTS_SPOTLIGHT_H

#include "components/color.h"
#include "components/light.h"
#include "components/vector.h"

namespace taeto
{

class Spotlight: public Light
{
public:
    Spotlight();

    Spotlight(Color, float, int);

    inline Color get_color(long int, long int, long int);

    inline Vector get_vector(long int, long int, long int);

private:
    Color color_;

    Vector vector_;

    unsigned int radius_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_SPOTLIGHT_H
