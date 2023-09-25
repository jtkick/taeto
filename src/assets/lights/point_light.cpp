#include "assets/lights/point_light.hpp"

#include <cmath>

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/position.hpp"

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

inline taeto::Color PointLight::color(taeto::Position p)
{
    // Get distance between points
    // Multiply y difference by two plus a bit since characters are about twice
    // as tall as they are wide
    long int distance = std::sqrt(
        (position_.x() - p.x()) * (position_.x() - p.x()) +
        (2.5 * (position_.y() - p.y())) * (2.5 * (position_.y() - p.y())) +
        (position_.z() - p.z()) * (position_.z() - p.z()));

    // Construct new color based on the distance
    taeto::Color new_color = taeto::Color(
        color_.red * std::pow(std::sqrt(fade_), distance),
        color_.green * std::pow(std::sqrt(fade_), distance),
        color_.blue * std::pow(std::sqrt(fade_), distance)
    );

    return new_color;
}

inline taeto::Vector PointLight::vector(taeto::Position p)
{
    return taeto::Vector(
        position_.x() - p.x(),
        position_.y() - p.y(),
        position_.z() - p.z());
}

}   // namespace taeto
