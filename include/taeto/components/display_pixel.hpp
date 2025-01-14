#ifndef COMPONENTS_DISPLAY_PIXEL_HPP_
#define COMPONENTS_DISPLAY_PIXEL_HPP_

#include "taeto/components/render_pixel.hpp"

#include <glm/vec4.hpp>

namespace taeto
{

class DisplayPixel
{
public:
    // Constructors
    DisplayPixel();

    DisplayPixel(char);

    DisplayPixel(char, glm::vec4, glm::vec4, bool);

    DisplayPixel(char, glm::vec4, glm::vec4, bool, bool, bool, bool);

    DisplayPixel(taeto::RenderPixel);

    // Reset to default values
    void clear();

    // Export to string
    std::string serialize();

    // Actual character to print
    char c;

    // Color of this 'pixel'
    // Based on whatever color palette is set in the engine
    glm::vec4 fg_color;

    // Color of background of 'pixel'
    glm::vec4 bg_color;

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
