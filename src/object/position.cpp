#include "object/position.hpp"

#include <algorithm>
#include <cmath>

namespace taeto
{

Position operator+(const Position& lhs, const Position& rhs)
{
    Position result = lhs;
    result += rhs;
    return result;
}

Position operator-(const Position& lhs, const Position& rhs)
{
    Position result = lhs;
    result -= rhs;
    return result;
}

Position& Position::operator+=(const Position& rhs)
{
    z_ += rhs.z_;
    y_ += rhs.y_;
    x_ += rhs.x_;

    return *this;
}

Position& Position::operator-=(const Position& rhs)
{
    z_ -= rhs.z_;
    y_ -= rhs.y_;
    x_ -= rhs.x_;

    return *this;
}

Position& Position::operator=(Position rhs)
{
    // std::swap(rhs);
    // return *this;

    // IDGAS
    z_ = rhs.z_;
    y_ = rhs.y_;
    x_ = rhs.x_;

    return *this;
}

double Position::distance(const Position& p1, const Position& p2)
{
    return sqrt(((p1.z_ - p2.z_) * (p1.z_ - p2.z_)) +
                ((p1.y_ - p2.y_) * (p1.y_ - p2.y_)) +
                ((p1.x_ - p2.x_) * (p1.x_ - p2.x_)));
}

}   // namespace taeto
