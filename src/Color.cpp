#include "Color.h"

#define RED_INDEX 0
#define GREEN_INDEX 1
#define BLUE_INDEX 2
#define ALPHA_INDEX 3

#define K (1 << (8 - 1))

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

Color::Color(void)
{

}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
    rgba[RED_INDEX]   = red;
    rgba[GREEN_INDEX] = green;
    rgba[BLUE_INDEX]  = blue;
    rgba[ALPHA_INDEX] = 255;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    rgba[RED_INDEX]   = red;
    rgba[GREEN_INDEX] = green;
    rgba[BLUE_INDEX]  = blue;
    rgba[ALPHA_INDEX] = alpha;
}

uint8_t Color::get_red() const
{
    return rgba[RED_INDEX];
}

uint8_t Color::get_green() const
{
    return rgba[GREEN_INDEX];
}

uint8_t Color::get_blue() const
{
    return rgba[BLUE_INDEX];
}

uint8_t Color::get_alpha() const
{
    return rgba[ALPHA_INDEX];
}

void Color::set_red(uint8_t red)
{
    rgba[RED_INDEX] = red;
}

void Color::set_green(uint8_t green)
{
    rgba[GREEN_INDEX] = green;
}

void Color::set_blue(uint8_t blue)
{
    rgba[BLUE_INDEX] = blue;
}

void Color::set_alpha(uint8_t alpha)
{
    rgba[ALPHA_INDEX] = alpha;
}

void Color::set_all(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    rgba[RED_INDEX] = r;
    rgba[GREEN_INDEX] = g;
    rgba[BLUE_INDEX] = b;
    rgba[ALPHA_INDEX] = a;
}

void Color::set_brightness(uint8_t brightness)
{
    // Scale all colors
    for (int i = 0; i < 3; i++)
        rgba[i] = q8_mul(rgba[i], brightness);
}

void Color::from_iterm(uint8_t i_color)
{
    // Pull RGB values from lookup table
    // Default to fully opaque
    for (int i = 0; i < 3; i++)
        rgba[i] = COLOR_TABLE[i_color][i];

    rgba[ALPHA_INDEX] = 255;
}

// I literally cannot believe this function worked on the first try.
// Lol, what a mess
// This method takes this object's RGB color and returns the closest 
// x-term color number
uint8_t Color::to_iterm() const
{
    int increments_length = 6;
    int increments[6] = { 0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff };
    
    int closest_color[3] = { 0 };
    
    for (int color = 0; color < 3; color++)
    {
        for (int i = 0; i < increments_length - 1; i++)
        {
            int smaller = increments[i];
            int bigger = increments[i+1];
            
            if (smaller <= rgba[color] && rgba[color] <= bigger)
            {
                int smaller_diff = abs(smaller - rgba[color]);
                int bigger_diff = abs(bigger - rgba[color]);
                
                if (smaller_diff < bigger_diff)
                    closest_color[color] = smaller;
                else
                    closest_color[color] = bigger;
            }
        }
    }
    
    // Find closest color in table
    int match_index;
    for (match_index = 0; match_index < 256; match_index++)
    {
        // Compare all color values
        if (closest_color[0] == COLOR_TABLE[match_index][0] &&
            closest_color[1] == COLOR_TABLE[match_index][1] &&
            closest_color[2] == COLOR_TABLE[match_index][2])
            break;
            
    }
    
    // If index is 256, there wasn't a match
    if (match_index != 256)
        return match_index;
    else
        throw "Couldn't find color in table.";
}

Color Color::operator * (const Color &c)
{
    Color new_color;
    
    new_color.set_red(q8_mul(rgba[RED_INDEX], c.get_red()));
    new_color.set_green(q8_mul(rgba[GREEN_INDEX], c.get_green()));
    new_color.set_blue(q8_mul(rgba[BLUE_INDEX], c.get_blue()));
    
    return new_color;
}
/*
void Color::operator = (const Color &c)
{
    rgba[0] = c.get_red();
    rgba[1] = c.get_green();
    rgba[2] = c.get_blue();
    rgba[3] = c.get_alpha();

}*/
