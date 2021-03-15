#include <Directional_Light.h>

Directional_Light::Directional_Light()
{

}

Directional_Light::Directional_Light(Color c, Vector v)
{
    color = c;
    vector = v;
}

Color Directional_Light::get_color(long int x, long int y, long int z)
{
    return color;
}

Vector Directional_Light::get_vector(long int x, long int y, long int z)
{
    return vector;
}
