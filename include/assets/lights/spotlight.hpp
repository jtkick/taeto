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

    Spotlight(taeto::Color, float, int);

    inline taeto::Color get_color(long int, long int, long int);

    inline taeto::Vector get_vector(long int, long int, long int);

private:
    taeto::Color color_;

    taeto::Vector vector_;

    unsigned int radius_;

    float fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_SPOTLIGHT_H
