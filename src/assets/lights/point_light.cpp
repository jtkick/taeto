#include "assets/lights/point_light.hpp"

#include <cmath>

#include <glm/glm.hpp>

namespace taeto
{

PointLight::PointLight()
{
    color_ = glm::vec3(1.0, 1.0, 1.0);
    fade_ = 0;
}

PointLight::PointLight(glm::vec3 c, float f)
{
    color_ = c;
    fade_ = f;
}

inline glm::vec3 PointLight::color(glm::dvec3 p)
{
    // Get distance between points
    // Multiply y difference by two plus a bit since characters are about twice
    // as tall as they are wide
    double distance = std::sqrt(
        (position_.x - p.x) * (position_.x - p.x) +
        (2.5 * (position_.y - p.y)) * (2.5 * (position_.y - p.y)) +
        (position_.z - p.z) * (position_.z - p.z));

    // Construct new color based on the distance
    return glm::vec3(
        color_.x * std::pow(std::sqrt(fade_), distance),
        color_.y * std::pow(std::sqrt(fade_), distance),
        color_.z * std::pow(std::sqrt(fade_), distance)
    );
}

inline glm::vec3 PointLight::vector(glm::dvec3 p)
{
    return glm::vec3(position_.x - p.x, position_.y - p.y, position_.z - p.z);
}

}   // namespace taeto
