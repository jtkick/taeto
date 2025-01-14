#include "taeto/components/render_pixel.hpp"

#include <glm/glm.hpp>

namespace taeto
{

RenderPixel::RenderPixel()
{
    render = true;
    c = ' ';
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = glm::vec3(0, 0, 1);
    specularity = 0.0;
}

RenderPixel::RenderPixel(char character)
{
    render = true;
    c = character;
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = glm::vec3(0.0, 0.0, 1.0);
    specularity = 0.0;
}

RenderPixel::RenderPixel(char ch, glm::vec4 fc, glm::vec4 bc, bool b)
{
    render = true;
    c = ch;
    fg_color = fc;
    bg_color = bc;
    bold = b;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = glm::vec3(0.0, 0.0, 1.0);
    specularity = 0.0;
}

RenderPixel::RenderPixel(
    char ch,
    glm::vec4 fc,
    glm::vec4 bc,
    bool b,
    bool i,
    bool u,
    bool s,
    glm::vec3 n,
    float sp)
{
    render = true;
    c = ch;
    fg_color = fc;
    bg_color = bc;
    bold = b;
    italic = i;
    underline = u;
    strikethrough = s;
    normal = n;
    specularity = sp;
}

// Helper functions
// Reset values to default
void RenderPixel::clear()
{
    render = true;
    c = ' ';
    fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    bg_color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    bold = false;
    italic = false;
    underline = false;
    strikethrough = false;
    normal = glm::vec3(0.0, 0.0, 1.0);
    specularity = 0.0;
}

/*
bool operator == (const Pixel& p1, const Pixel& p2)
{
    return (p1.get_char() == p2.get_char() &&
            p1.get_fg_color() == p2.get_fg_color() &&
            p1.get_bg_color() == p2.get_bg_color() &&
            p1.get_bold() == p2.get_bold());
}
*/

// void RenderPixel::operator = (const Pixel &p)
// {
//     c = p.c;
//     fg_color = p.fg_color;
//     bg_color = p.bg_color;
//     bold = p.bold;
//     underline = p.underline;
//     normal = p.normal;
//     collide = p.collide;
// }

// TODO: UPDATE THIS
// This function combines pixels, applying the right pixel
// onto the left pixel. Taking color alpha into account
// taeto::RenderPixel RenderPixel::operator & (const taeto::RenderPixel &p)
// {
//     taeto::RenderPixel new_pixel;
//
//     // Only combine if foreground color is not fully transparent
//     if (p.fg_color.w != 0)
//     {
//         // Write char
//         new_pixel.c = p.c;
//
//         // Write foreground color
//         new_pixel.fg_color = fg_color & p.fg_color;
//
//         // Write background color
//         new_pixel.bg_color = bg_color & p.bg_color;
//
//         // Write bold
//         new_pixel.bold = p.bold;
//
//         // Write underline
//         new_pixel.underline = p.underline;
//     }
//
//     return new_pixel;
// }

// This function combines pixels, element by element
// If both pixels have the same property defined, it is undefined behavior
// and the function will throw an error
/*
void RenderPixel::operator + (const RenderPixel &p)
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
    if (fg_color >= 0 && p.get_fg_color() < 0)
        ; // no-op
    else if (fg_color < 0 && p.get_fg_color() >= 0)
        fg_color = p.get_fg_color();
    else if (fg_color < 0 && p.get_fg_color() < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both foreground colors defined.";

    // Combine background color
    if (bg_color >= 0 && p.get_bg_color() < 0)
        ; // no-op
    else if (bg_color < 0 && p.get_bg_color() >= 0)
        bg_color = p.get_bg_color();
    else if (bg_color < 0 && p.get_bg_color() < 0)
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


// TODO: UPDATE THIS
// std::string RenderPixel::serialize()
// {
//     std::string s = "";
//
//     // Open pixel
//     s += "{";
//
//     // Add char
//     s += "\'" + std::to_string(c) + "\',";
//
//     // Add foreground color
//     s += fg_color.serialize() + ",";
//
//     // Add background color
//     s += bg_color.serialize() + ",";
//
//     // Add bold
//     s += std::to_string(bold) + ",";
//
//     // Add italic
//     s += std::to_string(italic) + ",";
//
//     // Add underline
//     s += std::to_string(underline) + ",";
//
//     // Add strikethrough
//     s += std::to_string(strikethrough) + ",";
//
//     // Add normal
//     s += normal.serialize();
//
//     // Close pixel
//     s += "}";
//
//     return s;
// }

}   // namespace taeto
