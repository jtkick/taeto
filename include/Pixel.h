#ifndef PIXEL
#define PIXEL

#include <Color.h>
#include <Vector.h>

#include <cmath>
#include <memory>

using namespace std;

class Pixel
{
    private:

        // Actual character to print
        char c;

        // Color of this 'pixel'
        // Based on whatever color palette is set in the engine
        Color foreground_color;

        // Color of background of 'pixel'
        Color background_color;

        // Whether or not this 'pixel' should be printed in bold
        bool bold;

        // Whether or not the 'pixel' is underlined
        bool underline;

        // Normal vector
        Vector normal;

        // Whether or not to do collision detection on this pixel
        bool collide;

    public:

        // Constructors
        Pixel();

        Pixel(char);

        Pixel(char, Color, Color, bool);

        // Getters
        char get_char() const;

        const Color* get_foreground_color() const;

        const Color* get_background_color() const;

        bool get_bold() const;

        bool get_underline() const;

        const Vector* get_normal() const;

        bool get_collide() const;

        // Setters
        void set_char(char);

        void set_foreground_color(Color);

        void set_background_color(Color);

        void set_bold(bool);

        void set_underline(bool);

        void set_normal(Vector);

        void set_collide(bool);

        Pixel operator & (const Pixel &p);

        void operator = (const Pixel &p);

        // Reset to default values
        void clear();

        //void operator + (const Pixel &p);
};

#endif
