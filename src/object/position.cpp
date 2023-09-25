#include "object/position.hpp"

#include <algorithm>
#include <cmath>

namespace taeto
{

inline const double& Position::z() const
{
    return z_;
}

inline void Position::z(const double& z)
{
    z_ = z;
}

inline const double& Position::y() const
{
    return y_;
}

inline void Position::y(const double& y)
{
    y_ = y;
}

inline const double& Position::x() const
{
    return x_;
}

inline void Position::x(const double& x)
{
    x_ = x;
}

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
}

double Position::distance(const Position& p1, const Position& p2)
{
    return sqrt(((p1.z_ - p2.z_) * (p1.z_ - p2.z_)) +
                ((p1.y_ - p2.y_) * (p1.y_ - p2.y_)) +
                ((p1.x_ - p2.x_) * (p1.x_ - p2.x_)));
}

}   // namespace taeto
