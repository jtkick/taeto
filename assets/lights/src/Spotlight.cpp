#include <Spotlight.h>

Spotlight::Spotlight()
{

}

Spotlight::Spotlight(Color c, float f, int i)
{
    color = c;
    fade = f;
    radius = i;
}

Color Spotlight::get_color(long int x, long int y, long int z)
{
    // Get distance between points
    // Multiply y difference by two since characters are exactly twice as tall as they are wide
    // Actually, fudge to a little more than two because it looks better to the eye
    // As a spotlight, z distance has no effect, since it goes on forever on that axis
    long int distance = sqrt(pow((x_position - x), 2) + pow(2.3 * (y_position - y), 2)) - radius;

    if (distance < 0)
        distance = 0;

    Color new_color = color;

    new_color.set_red(color.get_red() * pow(sqrt(fade), distance));
    new_color.set_green(color.get_green() * pow(sqrt(fade), distance));
    new_color.set_blue(color.get_blue() * pow(sqrt(fade), distance));

    return new_color;
}

Vector Spotlight::get_vector(long int x, long int y, long int z)
{

}
