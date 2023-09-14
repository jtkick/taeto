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

    ~Position();

    inline const double& z() const;

    inline void z(const double&);

    inline const double& y() const;

    inline void y(const double&);

    inline const double& x() const;

    inline void x(const double&);

    inline Position operator+(const Position& rhs);
    inline Position operator-(const Position& rhs);
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
