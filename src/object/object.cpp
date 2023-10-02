#include "object/object.hpp"

namespace taeto
{

taeto::Position& Object::position()
{
    return position_;
}

void Object::position(const taeto::Position& p)
{
    position_ = p;
}

void Object::move(double z, double y, double x)
{
    position_ += taeto::Position(z, y, x);
}

void Object::move(const taeto::Position& p)
{
    position_ += p;
}

}   // namespace taeto
