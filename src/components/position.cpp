#include "components/position.hpp"

#include <cmath>
#include <cstdint>

namespace taeto
{

Position::Position()
{
    z_ = 0;
    y_ = 0;
    x_ = 0;
}

Position::Position(double z, double y, double x)
{
    z_ = z;
    y_ = y;
    x_ = x;
}

double Position::distance(const Position& p1, const Position& p2)
{
    return sqrt(((p1.z_ - p2.z_) * (p1.z_ - p2.z_)) +
                ((p1.y_ - p2.y_) * (p1.y_ - p2.y_)) +
                ((p1.x_ - p2.x_) * (p1.x_ - p2.x_)));
}


}   // namespace taeto
