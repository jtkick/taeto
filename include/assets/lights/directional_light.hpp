#ifndef ASSETS_LIGHTS_DIRECTIONAL_LIGHT_H_
#define ASSETS_LIGHTS_DIRECTIONAL_LIGHT_H_

#include "components/color.h"
#include "components/light.h"
#include "components/vector.h"

namespace taeto
{

class DirectionalLight: public Light
{
public:
    DirectionalLight();

    DirectionalLight(taeto::Color, taeto::Vector);

    inline taeto::Color get_color(long int, long int, long int);

    inline taeto::Vector get_vector(long int, long int, long int);

private:
    taeto::Color color_;

    taeto::Vector vector_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_DIRECTIONAL_LIGHT_H_
