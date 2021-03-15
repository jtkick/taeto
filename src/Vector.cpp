#include "Vector.h"

#include <cmath>
#include <iostream>

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(char a, char b, char c)
{
    x = a;
    y = b;
    z = c;
}

Vector::~Vector()
{

}

// Getters
char Vector::get_x_component() const
{
    return x;
}

char Vector::get_y_component() const
{
    return y;
}

char Vector::get_z_component() const
{
    return z;
}

// Setters
void Vector::set_x_component(char c)
{
    x = c;
    
    if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) > 127)
        set_magnitude(127);
}

void Vector::set_y_component(char c)
{
    y = c;
    
    if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) > 127)
        set_magnitude(127);
}

void Vector::set_z_component(char c)
{
    z = c;
    
    if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) > 127)
        set_magnitude(127);
}

void Vector::set_all(char xc, char yc, char zc)
{
    x = xc;
    y = yc;
    z = zc;
}

void Vector::set_magnitude(char mag)
{
    if (mag > 127)
    {
        std::cout << "Cannot set magnitude greater than 127.\n";
        throw "Cannot set magnitude greater than 127.";
    }

    // Get current magnitude
    double factor = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) / mag;
        
    // Normalize all components to this value
    x = (char)(x / factor);
    y = (char)(y / factor);
    z = (char)(z / factor);
}

char Vector::get_magnitude()
{
    return (char)(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));;
}
