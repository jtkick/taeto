#include "assets/lights/spotlight.hpp"

#include <cmath>

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/position.hpp"

namespace taeto
{

Spotlight::Spotlight()
{
    color_ = taeto::Color(255, 255, 255, 255);
    fade_ = 0.8;
    radius_ = 30;
}

Spotlight::Spotlight(taeto::Color c, float f, int i)
{
    color_ = c;
    fade_ = f;
    radius_ = i;
}

inline taeto::Color Spotlight::color(taeto::Position p)
{
    // Get distance between points
    // Multiply y difference by two since characters are about twice as tall
    // as they are wide
    // Actually, fudge to a little more than two because it looks better to the
    // eye
    // As a spotlight, z distance has no effect, since it goes on forever on
    // that axis
    long int distance = sqrt(
        (position_.x - p.x) * (position_.x - p.x) +
        (2.5 * (position_.y - p.y)) * (2.5 * (position_.y - p.y))
    ) - radius_;

    // For sanity's sake
    if (distance < 0)
        distance = 0;

    // Construct new color based on the distance
    taeto::Color new_color = taeto::Color(
        color_.red * pow(sqrt(fade_), distance),
        color_.green * pow(sqrt(fade_), distance),
        color_.blue * pow(sqrt(fade_), distance)
    );

    return new_color;
}

inline taeto::Vector Spotlight::vector(taeto::Position p)
{
    // For now, spotlights point directly into the frame
    return taeto::Vector(0, 0, 127);
}

}   // namespace taeto
