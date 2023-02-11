#ifndef COMPONENTS_LIGHT_H_
#define COMPONENTS_LIGHT_H_

#include "components/color.h"
#include "components/vector.h"

namespace taeto
{

class Light
{
    protected:

        Color color;

        long int x_position;
        long int y_position;
        long int z_position;

    public:

        // Constructor
        Light();

        // Constructor with location initialization
        Light(long int, long int, long int);

        // Destructor
        ~Light();

        // This function returns what direction the light is traveling in with respect
        // to the given coordinate.
        virtual Vector get_vector(long int, long int, long int);

        // Return what color the light is at the given location
        // Usually doesn't change with location
        virtual Color get_color(long int, long int, long int);

        void set_color(Color);

        // Moves light relative to current location
        void move(long int, long int, long int);

        // Moves light to absolute position
        void place(long int, long int, long int);
};

}   // namespace taeto

#endif  // COMPONENTS_LIGHT_H_
