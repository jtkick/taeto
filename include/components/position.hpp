#ifndef COMPONENTS_POSITION_HPP_
#define COMPONENTS_POSITION_HPP_

#include <cstdint>

namespace taeto
{

// Point in space in the game world
class Position
{
public:
    Position();

    Position(int64_t, int64_t, int64_t);

    ~Position();

    static inline double distance(const Position&, const Position&);

    int64_t z;
    int64_t y;
    int64_t x;
};

}   // namespace taeto

#endif  // COMPONENTS_POSITION_HPP_
