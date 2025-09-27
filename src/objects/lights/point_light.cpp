#include "taeto/objects/lights/point_light.hpp"

#include <cmath>

#include <glm/glm.hpp>

namespace taeto
{

glm::vec3 PointLight::color(const glm::dvec3& pos)
{
    // Get distance between points
    // Multiply y difference by two plus a bit since characters are about twice
    // as tall as they are wide
    glm::dvec3 p = this->position();
    double distance = std::sqrt(
        (p.x - pos.x) * (p.x - pos.x) +
        (2.5 * (p.y - pos.y)) * (2.5 * (p.y - pos.y)) +
        (p.z - pos.z) * (p.z - pos.z));

    // Construct new color based on the distance
    return glm::vec3(
        color_.x * std::pow(std::sqrt(fade_), distance),
        color_.y * std::pow(std::sqrt(fade_), distance),
        color_.z * std::pow(std::sqrt(fade_), distance)
    );
}

glm::vec3 PointLight::vector(const glm::dvec3& pos)
{
    return pos - this->position();
    // return glm::vec3(p.x - position_.x, p.y - position_.y, p.z - position_.z);
}

}   // namespace taeto
