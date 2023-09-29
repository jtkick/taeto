#include "components/color.hpp"

namespace taeto
{

int const K = (1 << (8 - 1));

//////////////////////////////////////
//          HELPER METHODS          //
//////////////////////////////////////

uint8_t sat8(uint16_t x)
{
    if (x > 0xFF)
        return 0xFF;
    else if (x < 0x00)
        return 0x00;
    else
        return (uint8_t)x;
}

uint8_t q8_mul(uint8_t a, uint8_t b)
{
    uint8_t result;
    uint16_t temp;

    temp = (uint16_t)a * (uint16_t)b;

    temp += K;

    result = sat8(temp >> 8);

    return result;
}

uint8_t q8_div(uint8_t a, uint8_t b)
{
    int32_t temp = (int32_t)a << 8;

    if ((temp >= 0 && b >= 0) || (temp < 0 && b < 0))
        temp += b / 2;
    else
        temp -= b / 2;

    return (uint8_t)(temp / b);
}

Color::Color(void)
{

}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
    red   = r;
    green = g;
    blue  = b;
    alpha = 255;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    red   = r;
    green = g;
    blue  = b;
    alpha = a;
}

void Color::set_all(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

void Color::set_brightness(uint8_t brightness)
{
    // Scale all colors
    red = q8_mul(red, brightness);
    green = q8_mul(green, brightness);
    blue = q8_mul(blue, brightness);
}

// void Color::from_iterm(uint8_t i_color)
// {
//     // Pull RGB values from lookup table
//     // Default to fully opaque
//     for (int i = 0; i < 3; i++)
//         rgba[i] = COLOR_TABLE[i_color][i];
//
//     rgba[ALPHA_INDEX] = 255;
// }
//
// // This method takes this object's RGB color and returns the closest
// // x-term color number
// uint8_t Color::to_iterm() const
// {
//     int increments_length = 6;
//     int increments[6] = { 0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff };
//
//     int closest_color[3] = { 0 };
//
//     for (int color = 0; color < 3; color++)
//     {
//         for (int i = 0; i < increments_length - 1; i++)
//         {
//             int smaller = increments[i];
//             int bigger = increments[i+1];
//
//             if (smaller <= rgba[color] && rgba[color] <= bigger)
//             {
//                 int smaller_diff = abs(smaller - rgba[color]);
//                 int bigger_diff = abs(bigger - rgba[color]);
//
//                 if (smaller_diff < bigger_diff)
//                     closest_color[color] = smaller;
//                 else
//                     closest_color[color] = bigger;
//             }
//         }
//     }
//
//     // Find closest color in table
//     int match_index;
//     for (match_index = 0; match_index < 256; match_index++)
//     {
//         // Compare all color values
//         if (closest_color[0] == COLOR_TABLE[match_index][0] &&
//             closest_color[1] == COLOR_TABLE[match_index][1] &&
//             closest_color[2] == COLOR_TABLE[match_index][2])
//             break;
//
//     }
//
//     // If index is 256, there wasn't a match
//     if (match_index != 256)
//         return match_index;
//     else
//     {
//         throw "Couldn't find color in table.";
//     }
// }

// Mix colors additively
Color Color::operator + (const Color &c)
{
    Color new_color;

    new_color.red = red + c.red < 255 ? red + c.red : 255;
    new_color.green = green + c.green < 255 ? green + c.green : 255;
    new_color.blue = blue + c.blue < 255 ? blue + c.blue : 255;
    new_color.alpha = alpha + c.alpha < 255 ? alpha + c.alpha : 255;

    return new_color;
}

Color Color::operator - (const Color &c)
{
    Color r(0, 0, 0, 255);
    r.alpha = 255 - q8_mul((255 - alpha), (255 - c.alpha));
    r.red = q8_div(q8_mul(c.red, c.red), r.alpha) + q8_div(q8_mul(q8_mul(red, alpha), (255 - c.alpha)), r.alpha);
    r.green = q8_div(q8_mul(c.green, c.alpha), r.alpha) + q8_div(q8_mul(q8_mul(green, alpha), (255 - c.alpha)), r.alpha);
    r.blue = q8_div(q8_mul(c.blue, c.alpha), r.alpha) + q8_div(q8_mul(q8_mul(blue, alpha), (255 - c.alpha)), r.alpha);

    return r;
}

// Mix colors subtractively
Color Color::operator & (const Color &c)
{

    // Try more sophisticated method, that takes alpha into account
    Color new_color;

    float t_alpha = (float)(alpha) / 255;
    float c_alpha = (float)(c.alpha) / 255;

    new_color.red = red * t_alpha * (1 - c_alpha) + c.red * c_alpha;
    new_color.green = green * t_alpha * (1 - c_alpha) + c.green * c_alpha;
    new_color.blue = blue * t_alpha * (1 - c_alpha) + c.blue * c_alpha;
    new_color.alpha = (t_alpha * (1 - c_alpha) + c_alpha) * 255;

    return new_color;
}

struct vec4
{
    double r;
    double g;
    double b;
    double a;
};

// TODO: TRY THIS ONE INSTEAD
Color Color::operator & (const Color &c)
{
    // We're going to move to vec3 soon, so just convert to floats
    vec4 c1 = {(double)red/255, (double)green/255,
               (double)blue/255, (double)alpha/255};
    vec4 c1 = {(double)c.red/255, (double)c.green/255,
               (double)c.blue/255, (double)c.alpha/255};
    vec4 cr = {0, 0, 0, 0};

    cr.a = c1.a + (c2.a * (1 - c1.a));
    cr.r = ((c1.r * c1.a) + (c2.r * c2.a) * (1 - c1.a)) / cr.a;
    cr.g = ((c1.g * c1.a) + (c2.g * c2.a) * (1 - c1.a)) / cr.a;
    cr.b = ((c1.b * c1.a) + (c2.b * c2.a) * (1 - c1.a)) / cr.a;

    return Color(cr.r*255, cr.g*255, cr.b*255, cr.a*255);
}

Color Color::operator += (const Color &c)
{
    red = red + c.red < 255 ? red + c.red : 255;
    green = green + c.green < 255 ? green + c.green : 255;
    blue = blue + c.blue < 255 ? blue + c.blue : 255;
    alpha = alpha + c.alpha < 255 ? alpha + c.alpha : 255;

    return *this;
}

Color Color::operator -= (const Color &c)
{
    Color r(0, 0, 0, 255);
    r.alpha = 255 - q8_mul((255 - c.alpha), (255 - alpha));
    r.red = q8_div(q8_mul(c.red, c.red), r.alpha) + q8_div(q8_mul(q8_mul(red, alpha), (255 - c.alpha)), r.alpha);
    r.green = q8_div(q8_mul(c.green, c.alpha), r.alpha) + q8_div(q8_mul(q8_mul(green, alpha), (255 - c.alpha)), r.alpha);
    r.blue = q8_div(q8_mul(c.blue, c.alpha), r.alpha) + q8_div(q8_mul(q8_mul(blue, alpha), (255 - c.alpha)), r.alpha);

    // Copy values
    *this = r;

    return r;
}

Color Color::operator * (const Color &c)
{
    Color new_color;

    new_color.red = q8_mul(red, c.red);
    new_color.green = q8_mul(green, c.green);
    new_color.blue = q8_mul(blue, c.blue);
    new_color.alpha = alpha;

    return new_color;
}

void Color::operator = (const Color &c)
{
    red = c.red;
    green = c.green;
    blue = c.blue;
    alpha = c.alpha;
}

std::string Color::serialize()
{
    return "{" + std::to_string(red) + ","
               + std::to_string(green) + ","
               + std::to_string(blue) + ","
               + std::to_string(alpha) + "}";
}

}   // namespace taeto
