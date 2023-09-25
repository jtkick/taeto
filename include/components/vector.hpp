#ifndef COMPONENTS_VECTOR_HPP_
#define COMPONENTS_VECTOR_HPP_

#include <cmath>
#include <string>

namespace taeto
{


// TODO: FIX THIS WHOLE FUCKING CLASS
class Vector
{
private:
    // Each cartesian component
    char x_;
    char y_;
    char z_;

public:
    // Constructors
    Vector();

    Vector(char, char, char);

    // Destructor
    ~Vector();

    // Getters
    char x() const;

    char y() const;

    char z() const;

    // Setters
    void x(char);

    void y(char);

    void z(char);

    void set_all(char, char, char);

    // Other methods

    // Export to string, compatible with constructor
    std::string serialize();

    // Sets overall magnitude to given value
    void set_magnitude(char);

    // Returns current magnitude
    char get_magnitude();
};

}   // namespace taeto

#endif  // COMPONENTS_VECTOR_HPP_
