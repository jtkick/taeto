#include "components/position.hpp"

#include <cmath>
#include <cstdint>

namespace taeto
{

Position::Position()
{
    z = 0;
    y = 0;
    x = 0;
}

Position::Position(int64_t z_, int64_t y_, int64_t x_)
{
    z = z_;
    y = y_;
    x = x_;
}

double Position::distance(const Position& p1, const Position& p2)
{
    return sqrt(((p1.z - p2.z) * (p1.z - p2.z)) +
                ((p1.y - p2.y) * (p1.y - p2.y)) +
                ((p1.x - p2.x) * (p1.x - p2.x)));
}


}   // namespace taeto
