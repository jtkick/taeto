#include "assets/lights/point_light.hpp"

#include <cmath>

#include "components/color.hpp"
#include "components/vector.hpp"

namespace taeto
{

PointLight::PointLight()
{
    color_ = taeto::Color(255, 255, 255, 255);
    fade_ = 0;
}

PointLight::PointLight(taeto::Color c, float f)
{
    color_ = c;
    fade_ = f;
}

inline taeto::Color PointLight::light_color(
    unsigned long int x, unsigned long int y, unsigned long int z)
{
    // Get distance between points
    // Multiply y difference by two plus a bit since characters are about twice
    // as tall as they are wide
    long int distance = sqrt(
        (x_position_ - x) * (x_position_ - x) +
        (2.5 * (y_position_ - y)) * (2.5 * (y_position_ - y)) +
        (z_position_ - z) * (z_position_ - z));

    // Construct new color based on the distance
    taeto::Color new_color = taeto::Color(
        color_.red * pow(sqrt(fade_), distance),
        color_.green * pow(sqrt(fade_), distance),
        color_.blue * pow(sqrt(fade_), distance)
    );

    return new_color;
}

inline taeto::Vector PointLight::light_vector(
    unsigned long int x, unsigned long int y, unsigned long int z)
{
    return taeto::Vector(x_position_ - x, y_position_ - y, z_position_ - z);
}

}   // namespace taeto
