#include "components/display_pixel.hpp"

namespace taeto
{

DisplayPixel::DisplayPixel()
{
    c = ' ';
    foreground_color = taeto::Color(255, 255, 255, 255);
    background_color = taeto::Color(50, 50, 50, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char character)
{
    c = character;
    foreground_color = taeto::Color(255, 255, 255, 255);
    background_color = taeto::Color(50, 50, 50, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char ch, Color fc, Color bc, bool b)
{
    c = ch;
    foreground_color = fc;
    background_color = bc;
    bold = b;
    italic = false;
    underline = false;
    strikethrough = false;
}

DisplayPixel::DisplayPixel(char ch, Color fc, Color bc, bool b, bool i, bool u, bool s, Vector n)
{
    c = ch;
    foreground_color = fc;
    background_color = bc;
    bold = b;
    italic = i;
    underline = u;
    strikethrough = s;
}

// Helper functions
// Reset values to default
void DisplayPixel::clear()
{
    c = ' ';
    foreground_color.set_all(255, 255, 255, 255);
    background_color.set_all(0, 0, 0, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

}   // namespace taeto
