#include "taeto/objects/lights/spotlight.hpp"

#include <cmath>

#include <glm/glm.hpp>

namespace taeto
{

glm::vec3 Spotlight::color(const glm::dvec3& pos)
{
    // Get distance between points
    // Multiply y difference by two since characters are about twice as tall
    // as they are wide
    // Actually, fudge to a little more than two because it looks better to the
    // eye
    // As a spotlight, z distance has no effect, since it goes on forever on
    // that axis
    glm::dvec3 position = this->position();
    double distance = sqrt(
        (position.x - pos.x) * (position.x - pos.x) +
        (2.5 * (position.y - pos.y)) * (2.5 * (position.y - pos.y))
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

glm::vec3 Spotlight::vector(const glm::dvec3& pos)
{
    // We don't need the position to determine the vector; silence the warning
    (void)pos;

    // For now, spotlights point directly into the frame
    return glm::vec3(0.0, 0.0, -1.0);
}

}   // namespace taeto
