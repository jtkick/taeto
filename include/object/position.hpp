#ifndef OBJECT_POSITION_HPP_
#define OBJECT_POSITION_HPP_

namespace taeto
{

// Point in space in the game world
class Position
{
public:
    Position() = default;

    Position(double z, double y, double x)
        : z_{z}, y_{y}, x_{x} { };

    ~Position() { };

    inline const double& z() const { return z_; };

    inline void z(const double& z) { z_ = z; };

    inline const double& y() const { return y_; };

    inline void y(const double& y) { y_ = y; };

    inline const double& x() const { return x_; };

    inline void x(const double& x) { x_ = x; };

    // inline Position operator+(Position lhs, const Position& rhs);
    // inline Position operator-(Position lhs, const Position& rhs);
    Position& operator+=(const Position& rhs);
    Position& operator-=(const Position& rhs);
    Position& operator=(Position rhs);

    static inline double distance(const Position&, const Position&);

protected:
    double z_ = 0.0f;
    double y_ = 0.0f;
    double x_ = 0.0f;
};

}   // namespace taeto

#endif  // OBJECT_POSITION_HPP_
