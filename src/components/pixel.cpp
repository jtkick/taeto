#include "components/pixel.h"

namespace taeto
{

Pixel::Pixel()
{
    c = ' ';
    foreground_color = Color(255, 255, 255, 255);
    background_color = Color(50, 50, 50, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = Vector(0, 0, 1);
    collide = false;
}

Pixel::Pixel(char character)
{
    c = character;
    foreground_color = Color(255, 255, 255, 255);
    background_color = Color(50, 50, 50, 0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = Vector(0, 0, 1);
    collide = false;
}

Pixel::Pixel(char ch, Color fc, Color bc, bool b)
{
    c = ch;
    foreground_color = fc;
    background_color = bc;
    bold = b;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = Vector(0, 0, 1);
    collide = false;
}

Pixel::Pixel(char ch, Color fc, Color bc, bool b, bool i, bool u, bool s, Vector n)
{
    c = ch;
    foreground_color = fc;
    background_color = bc;
    bold = b;
    italic = i;
    underline = u;
    strikethrough = s;
    normal = n;
    collide = false;
}

// Helper functions
// Reset values to default
void Pixel::clear()
{
    c = ' ';
    foreground_color.set_all(255, 255, 255, 255);
    background_color.set_all(0, 0, 0, 0);
    bold = false;
    underline = false;
    normal.set_all(0, 0, 127);
    collide = false;
}

/*
bool operator == (const Pixel& p1, const Pixel& p2)
{
    return (p1.get_char() == p2.get_char() &&
            p1.get_foreground_color() == p2.get_foreground_color() &&
            p1.get_background_color() == p2.get_background_color() &&
            p1.get_bold() == p2.get_bold());
}
*/

// void Pixel::operator = (const Pixel &p)
// {
//     c = p.c;
//     foreground_color = p.foreground_color;
//     background_color = p.background_color;
//     bold = p.bold;
//     underline = p.underline;
//     normal = p.normal;
//     collide = p.collide;
// }

// This function combines pixels, applying the right pixel
// onto the left pixel. Taking color alpha into account
Pixel Pixel::operator & (const Pixel &p)
{
    Pixel new_pixel;

    // Only combine if foreground color is not fully transparent
    if (p.foreground_color.alpha != 0)
    {
        // Write char
        new_pixel.c = p.c;

        // Write foreground color
        new_pixel.foreground_color = foreground_color & p.foreground_color;

        // Write background color
        new_pixel.background_color = background_color & p.background_color;

        // Write bold
        new_pixel.bold = p.bold;

        // Write underline
        new_pixel.underline = p.underline;
    }

    return new_pixel;
}

// This function combines pixels, element by element
// If both pixels have the same property defined, it is undefined behavior
// and the function will throw an error
/*
void Pixel::operator + (const Pixel &p)
{
    // Combine char
    if (c >= 0 && p.get_char() < 0)
        ; // no-op
    else if (c < 0 && p.get_char() >= 0)
        c = p.get_char();
    else if (c < 0 && p.get_char() < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both characters defined.";

    // Combine foreground color
    if (foreground_color >= 0 && p.get_foreground_color() < 0)
        ; // no-op
    else if (foreground_color < 0 && p.get_foreground_color() >= 0)
        foreground_color = p.get_foreground_color();
    else if (foreground_color < 0 && p.get_foreground_color() < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both foreground colors defined.";

    // Combine background color
    if (background_color >= 0 && p.get_background_color() < 0)
        ; // no-op
    else if (background_color < 0 && p.get_background_color() >= 0)
        background_color = p.get_background_color();
    else if (background_color < 0 && p.get_background_color() < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both background colors defined.";

    // Combine bold property
    if (bold >= 0 && p.get_bold() < 0)
        ; // no-op
    else if (bold < 0 && p.get_bold() >= 0)
        bold = p.get_bold();
    else if (bold < 0 && p.get_bold() < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both bold properties defined.";

}
*/

std::string Pixel::serialize()
{
    std::string s = "";

    // Open pixel
    s += "{";

    // Add char
    s += "\'" + std::to_string(c) + "\',";

    // Add foreground color
    s += foreground_color.serialize() + ",";

    // Add background color
    s += background_color.serialize() + ",";

    // Add bold
    s += std::to_string(bold) + ",";

    // Add italic
    s += std::to_string(italic) + ",";

    // Add underline
    s += std::to_string(underline) + ",";

    // Add strikethrough
    s += std::to_string(strikethrough) + ",";

    // Add normal
    s += normal.serialize();

    // Close pixel
    s += "}";

    return s;
}

}   // namespace taeto
