#include "Light.h"

// Constructor
Light::Light()
{
    x_position = 0;
    y_position = 0;
    z_position = 0;
}
        
// Constructor with location initialization
Light::Light(long int x, long int y, long int z)
{
    x_position = x;
    y_position = y;
    z_position = z;
}
        
// Destructor
Light::~Light()
{

}

// This function returns what direction the light is traveling in with respect
// to the given coordinate.
Vector Light::get_vector(long int, long int, long int)
{

}
        
// Return what color the light is at the given location
// Usually doesn't change with location
Color Light::get_color(long int, long int, long int)
{

}

void Light::set_color(Color c)
{
    color = c;
}

// Moves light relative to current location
void Light::move(long int x_diff, long int y_diff, long int z_diff)
{
    x_position += x_diff;
    y_position += y_diff;
    z_position += z_diff;
}
