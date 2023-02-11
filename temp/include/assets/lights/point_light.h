#ifndef ASSETS_LIGHTS_POINT_LIGHT_H_
#define ASSETS_LIGHTS_POINT_LIGHT_H_

#include "components/color.h"
#include "components/light.h"
#include "components/vector.h"

namespace taeto
{

class PointLight: public Light
{
public:
    PointLight();

    PointLight(Color, float);

    inline Color get_color(long int, long int, long int);

    inline Vector get_vector(long int, long int, long int);

private:
    Color color_;

    Vector vector_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_POINT_LIGHT_H_
