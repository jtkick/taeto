#include "assets/lights/directional_light.hpp"

#include "components/color.hpp"
#include "components/vector.hpp"

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

inline taeto::Color DirectionalLight::light_color(
    unsigned long int x, unsigned long int y, unsigned long int z)
{
    return color_;
}

inline taeto::Vector DirectionalLight::light_vector(
    unsigned long int x, unsigned long int y, unsigned long int z)
{
    return vector_;
}

}   // namespace taeto
