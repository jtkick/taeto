#include "assets/lights/spotlight.hpp"

#include <cmath>

#include <glm/glm.hpp>

namespace taeto
{

Spotlight::Spotlight()
{
    color_ = glm::vec3(1.0, 1.0, 1.0);
    fade_ = 0.8;
    radius_ = 30;
}

Spotlight::Spotlight(glm::vec3 c, float f, int i)
{
    color_ = c;
    fade_ = f;
    radius_ = i;
}

glm::vec3 Spotlight::color(glm::dvec3 p)
{
    // Get distance between points
    // Multiply y difference by two since characters are about twice as tall
    // as they are wide
    // Actually, fudge to a little more than two because it looks better to the
    // eye
    // As a spotlight, z distance has no effect, since it goes on forever on
    // that axis
    double distance = sqrt(
        (position_.x - p.x) * (position_.x - p.x) +
        (2.5 * (position_.y - p.y)) * (2.5 * (position_.y - p.y))
    ) - radius_;

    // For sanity's sake
    if (distance < 0)
        distance = 0;

    // Construct new color based on the distance
    return glm::vec3(
        color_.x * pow(sqrt(fade_), distance),
        color_.y * pow(sqrt(fade_), distance),
        color_.z * pow(sqrt(fade_), distance)
    );
}

glm::vec3 Spotlight::vector(glm::dvec3 p)
{
    // For now, spotlights point directly into the frame
    return glm::vec3(0.0, 0.0, 1.0);
}

}   // namespace taeto
