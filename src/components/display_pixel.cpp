#include "components/display_pixel.hpp"

#include <glm/glm.hpp>

namespace taeto
{

DisplayPixel::DisplayPixel()
{
    c = ' ';
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char character)
{
    c = character;
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char ch, glm::vec4 fc, glm::vec4 bc, bool b)
{
    c = ch;
    fg_color = fc;
    bg_color = bc;
    bold = b;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char ch, glm::vec4 fc, glm::vec4 bc, bool b, bool i, bool u, bool s)
{
    c = ch;
    fg_color = fc;
    bg_color = bc;
    bold = b;
    italic = i;
    underline = u;
    strikethrough = s;
}

DisplayPixel::DisplayPixel(taeto::RenderPixel rp)
{
    c = rp.c;
    fg_color = rp.fg_color;
    bg_color = rp.bg_color;
    bold = rp.bold;
    italic = rp.italic;
    underline = rp.underline;
    strikethrough = rp.strikethrough;
}

// Helper functions
// Reset values to default
void DisplayPixel::clear()
{
    c = ' ';
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

}   // namespace taeto
