#include "assets/lights/directional_light.hpp"

#include "components/color.h"
#include "components/vector.h"

namespace taeto
{

DirectionalLight::DirectionalLight()
{
    color_ = taeto::Color(255, 255, 255, 255);
    vector_ = taeto::Vector(0, 0, 127);
}

DirectionalLight::DirectionalLight(taeto::Color c, taeto::Vector v)
{
    color_ = c;
    vector_ = v;
}

inline taeto::Color DirectionalLight::get_color(long int x, long int y, long int z)
{
    return color_;
}

inline taeto::Vector DirectionalLight::get_vector(long int x, long int y, long int z)
{
    return vector_;
}

}   // namespace taeto
