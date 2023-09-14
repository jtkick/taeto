#include "object/object.hpp"

const taeto::Position& Object::position() const
{
    return position_;
}

void Object::position(const taeto::Position& p)
{
    position_ = p;
}

void Object::move(double z, double y, double x) inline
{
    position_ += taeto::Position(z, y, x);
}

void Object::move(const taeto::Position& p) inline
{
    position_ += p;
}