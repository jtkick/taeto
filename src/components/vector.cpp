#include "components/vector.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace taeto
{

Vector::Vector()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Vector::Vector(char a, char b, char c)
{
    x_ = a;
    y_ = b;
    z_ = c;
}

Vector::~Vector()
{

}

// Getters
char Vector::x() const
{
    return x_;
}

char Vector::y() const
{
    return y_;
}

char Vector::z() const
{
    return z_;
}

// Setters
void Vector::x(char c)
{
    x_ = c;

    if (sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)) > 127)
        set_magnitude(127);
}

void Vector::y(char c)
{
    y_ = c;

    if (sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)) > 127)
        set_magnitude(127);
}

void Vector::z(char c)
{
    z_ = c;

    if (sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)) > 127)
        set_magnitude(127);
}

void Vector::set_all(char xc, char yc, char zc)
{
    x_ = xc;
    y_ = yc;
    z_ = zc;

    if (sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)) > 127)
        set_magnitude(127);
}

std::string Vector::serialize()
{
    return "{" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + "}";
}

void Vector::set_magnitude(char mag)
{
    if (mag > 127)
    {
        std::cout << "Cannot set magnitude greater than 127.\n";
        throw "Cannot set magnitude greater than 127.";
    }

    // Get current magnitude
    double factor = sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)) / mag;

    // Normalize all components to this value
    x_ = (char)(x_ / factor);
    y_ = (char)(y_ / factor);
    z_ = (char)(z_ / factor);
}

char Vector::get_magnitude()
{
    return (char)(sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)));;
}

}   // namespace taeto
