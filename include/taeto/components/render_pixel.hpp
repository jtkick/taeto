#ifndef COMPONENTS_RENDER_PIXEL_HPP_
#define COMPONENTS_RENDER_PIXEL_HPP_

#include <string>

#include <glm/glm.hpp>

namespace taeto
{

class RenderPixel
{
public:
    // Constructors
    RenderPixel();

    RenderPixel(char);

    RenderPixel(char, glm::vec4, glm::vec4, bool);

    RenderPixel(
        char,
        glm::vec4,
        glm::vec4,
        bool b,
        bool i,
        bool u,
        bool s,
        glm::vec3,
        float);

    taeto::RenderPixel operator & (const taeto::RenderPixel &p);

    // void operator = (const taeto::Pixel &p);

    // Reset to default values
    void clear();

    //void operator + (const taeto::Pixel &p);

    // Export to string
    std::string serialize();

    // Whether or not this pixel should be rendered
    // Useful for the edges of a sprite that isn't perfectly rectangular
    bool render;

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

    // Normal vector
    glm::vec3 normal;

    // How "shiny" this pixel is
    float specularity;
};

}   // namespace taeto

#endif  // COMPONENTS_RENDER_PIXEL_HPP_
