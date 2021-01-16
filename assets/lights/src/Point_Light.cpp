#include "Point_Light.h"

#include <cmath>

Point_Light::Point_Light()
{
    color = Color(255, 255, 255, 255);
    fade = 0;
}

Point_Light::Point_Light(Color c, float f)
{
    color = c;
    fade = f;
}

Color Point_Light::get_color(long int x, long int y, long int z)
{
    // Get distance between points
    // Multiply y difference by two since characters are exactly twice as tall as they are wide
    long int distance = sqrt(pow((x_position - x), 2) + pow(2 * (y_position - y), 2) + pow((z_position - z), 2));
        
    Color new_color = color;
    
    new_color.set_red(color.get_red() * pow(sqrt(fade), distance));
    new_color.set_green(color.get_green() * pow(sqrt(fade), distance));
    new_color.set_blue(color.get_blue() * pow(sqrt(fade), distance));
    
    return new_color;
}

Vector Point_Light::get_vector(long int x, long int y, long int z)
{
    return Vector(x_position - x, y_position - y, z_position - z);
}
