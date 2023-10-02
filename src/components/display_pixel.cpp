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

DisplayPixel::DisplayPixel(char ch, Color fc, Color bc, bool b, bool i, bool u, bool s)
{
    c = ch;
    foreground_color = fc;
    background_color = bc;
    bold = b;
    italic = i;
    underline = u;
    strikethrough = s;
}

DisplayPixel::DisplayPixel(taeto::RenderPixel rp)
{
    c = rp.c;
    foreground_color = rp.foreground_color;
    background_color = rp.background_color;
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
    foreground_color.set_all(255, 255, 255, 255);
    background_color.set_all(0, 0, 0, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
}

}   // namespace taeto
