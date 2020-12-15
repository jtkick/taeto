#include "Color.h"

#define RED_INDEX 0
#define GREEN_INDEX 1
#define BLUE_INDEX 2
#define ALPHA_INDEX 3

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

uint8_t Color::get_red()
{
    return rgba[RED_INDEX];
}

uint8_t Color::get_green()
{
    return rgba[GREEN_INDEX];
}

uint8_t Color::get_blue()
{
    return rgba[BLUE_INDEX];
}

uint8_t Color::get_alpha()
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
uint8_t Color::to_iterm()
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
