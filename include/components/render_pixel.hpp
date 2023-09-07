#ifndef COMPONENTS_RENDER_PIXEL_H_
#define COMPONENTS_RENDER_PIXEL_H_

#include <string>

#include "components/color.hpp"
#include "components/vector.hpp"

namespace taeto
{

class RenderPixel
{
public:
    // Constructors
    RenderPixel();

    RenderPixel(char);

    RenderPixel(char, Color, Color, bool);

    RenderPixel(char, Color, Color, bool, bool, bool, bool, Vector);

    taeto::RenderPixel operator & (const taeto::RenderPixel &p);

    // void operator = (const taeto::Pixel &p);

    // Reset to default values
    void clear();

    //void operator + (const taeto::Pixel &p);

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

    // Normal vector
    taeto::Vector normal;

    // How "shiny" this pixel is
    uint8_t specularity;

    // Whether or not to do collision detection on this pixel
    bool collide;
};

}   // namespace taeto

#endif  // COMPONENTS_RENDER_PIXEL_H_
