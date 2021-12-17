#ifndef VECTOR
#define VECTOR

#include <cmath>
#include <string>

using namespace std;

class Vector
{
    private:

        // Each cartesian component
        char x;
        char y;
        char z;

    public:

        // Constructors
        Vector();

        Vector(char, char, char);

        // Destructor
        ~Vector();

        // Getters
        char get_x_component() const;

        char get_y_component() const;

        char get_z_component() const;

        // Setters
        void set_x_component(char);

        void set_y_component(char);

        void set_z_component(char);

        void set_all(char, char, char);

        // Other methods

        // Export to string, compatible with constructor
        std::string serialize();

        // Sets overall magnitude to given value
        void set_magnitude(char);

        // Returns current magnitude
        char get_magnitude();
};

#endif
