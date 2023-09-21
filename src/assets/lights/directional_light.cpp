#include "assets/lights/directional_light.hpp"

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/position.hpp"

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

inline taeto::Color DirectionalLight::color(taeto::Position p)
{
    return color_;
}

inline taeto::Vector DirectionalLight::vector(taeto::Position p)
{
    return vector_;
}

}   // namespace taeto
