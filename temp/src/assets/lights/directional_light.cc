#include "assets/lights/directional_light.h"

#include "components/color.h"
#include "components/vector.h"

namespace taeto
{

DirectionalLight::DirectionalLight()
{
    color_ = Color(255, 255, 255, 255);
    vector_ = Vector(0, 0, 127);
}

DirectionalLight::DirectionalLight(Color c, Vector v)
{
    color_ = c;
    vector_ = v;
}

inline Color DirectionalLight::get_color(long int x, long int y, long int z)
{
    return color_;
}

inline Vector DirectionalLight::get_vector(long int x, long int y, long int z)
{
    return vector_;
}

}   // namespace taeto
