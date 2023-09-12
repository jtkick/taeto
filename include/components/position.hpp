#ifndef COMPONENTS_POSITION_HPP_
#define COMPONENTS_POSITION_HPP_

namespace taeto
{

// Point in space in the game world
class Position
{
public:
    Position();

    Position(double, double, double);

    ~Position();

    static inline double distance(const Position&, const Position&);

    Position operator+(const Position& rhs) const;
    Position operator-(const Position& rhs) const;
    Position operator+=(const Position& rhs) const;
    Position operator-=(const Position& rhs) const;
    Position operator=(const Position& rhs) const;

    double z_;
    double y_;
    double x_;
};

Position

}   // namespace taeto

#endif  // COMPONENTS_POSITION_HPP_
