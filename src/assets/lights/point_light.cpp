#include "assets/lights/point_light.hpp"

#include <cmath>

#include "components/color.h"
#include "components/vector.h"

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

inline taeto::Color PointLight::get_color(long int x, long int y, long int z)
{
    // Get distance between points
    // Multiply y difference by two plus a bit since characters are about twice
    // as tall as they are wide
    long int distance = sqrt(
        (x_position - x) * (x_position - x) +
        (2.5 * (y_position - y)) * (2.5 * (y_position - y)) +
        (z_position - z) * (z_position - z));

    // Construct new color based on the distance
    taeto::Color new_color = taeto::Color(
        color_.red * pow(sqrt(fade_), distance),
        color_.green * pow(sqrt(fade_), distance),
        color_.blue * pow(sqrt(fade_), distance)
    );

    return new_color;
}

inline taeto::Vector PointLight::get_vector(long int x, long int y, long int z)
{
    return taeto::Vector(x_position - x, y_position - y, z_position - z);
}

}   // namespace taeto
