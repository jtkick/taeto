#ifndef COMPONENTS_DISPLAY_PIXEL_HPP_
#define COMPONENTS_DISPLAY_PIXEL_HPP_

#include <string>

#include "components/color.hpp"
#include "components/vector.hpp"

namespace taeto
{

class DisplayPixel
{
public:
    // Constructors
    DisplayPixel();

    DisplayPixel(char);

    DisplayPixel(char, Color, Color, bool);

    DisplayPixel(char, Color, Color, bool, bool, bool, bool);

    // Reset to default values
    void clear();

    // Export to string
    std::string serialize();

    // Actual character to print
    char c;

    // Color of this 'pixel'
    // Based on whatever color palette is set in the engine
    taeto::Color foreground_color;

    // Color of background of 'pixel'
    taeto::Color background_color;

    // Whether or not this 'pixel' should be printed in bold
    bool bold;

    // Whether the char is italicized
    bool italic;

    // Whether or not the 'pixel' is underlined
    bool underline;

    // Whether the character has a line through it
    bool strikethrough;
};

}   // namespace taeto

#endif  // COMPONENTS_DISPLAY_PIXEL_HPP_
