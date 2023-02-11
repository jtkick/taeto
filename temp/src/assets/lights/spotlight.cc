#include "assets/lights/spotlight.h"

#include <cmath>

#include "components/color.h"
#include "components/vector.h"

namespace taeto
{

Spotlight::Spotlight()
{
    color_ = Color(255, 255, 255, 255);
    fade_ = 0.8;
    radius_ = 30;
}

Spotlight::Spotlight(Color c, float f, int i)
{
    color_ = c;
    fade_ = f;
    radius_ = i;
}

inline Color Spotlight::get_color(long int x, long int y, long int z)
{
    // Get distance between points
    // Multiply y difference by two since characters are about twice as tall
    // as they are wide
    // Actually, fudge to a little more than two because it looks better to the
    // eye
    // As a spotlight, z distance has no effect, since it goes on forever on
    // that axis
    long int distance = sqrt(
        (x_position - x) * (x_position - x) +
        (2.5 * (y_position - y) * (2.5 * (y_position - y))
    ) - radius;

    // For sanity's sake
    if (distance < 0)
        distance = 0;

    // Construct new color based on the distance
    Color new_color = Color(
        red = color_.red * pow(sqrt(fade), distance);
        green = color_.green * pow(sqrt(fade), distance);
        blue = color_.blue * pow(sqrt(fade), distance);
    );

    return new_color;
}

inline Vector Spotlight::get_vector(long int x, long int y, long int z)
{
    // For now, spotlights point directly into the frame
    return Vector(0, 0, 127);
}

}   // namespace taeto
