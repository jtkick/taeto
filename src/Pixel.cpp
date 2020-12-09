#include "Pixel.h"

Pixel::Pixel()
{

}


Pixel::Pixel(char, int16_t, int16_t, int8_t)
{

}
        
// Getters and setters
char Pixel::get_char() const
{
    return c;
}

        
uint8_t Pixel::get_foreground_color() const
{
    return foreground_color;
}

        
uint8_t Pixel::get_background_color() const
{
    return background_color;
}

        
bool Pixel::get_bold() const
{
    return bold;
}

        
void Pixel::set_char(char new_char)
{
    c = new_char;
}

        
void Pixel::set_foreground_color(uint8_t color)
{
    foreground_color = color;
}
        
void Pixel::set_background_color(uint8_t color)
{
    background_color = color;
}
        
void Pixel::set_bold(bool b)
{
    bold = b;
}

    
bool operator == (const Pixel& p1, const Pixel& p2)
{
    return (p1.get_char() == p2.get_char() &&
            p1.get_foreground_color() == p2.get_foreground_color() &&
            p1.get_background_color() == p2.get_background_color() &&
            p1.get_bold() == p2.get_bold());
}


void Pixel::operator = (const Pixel &p)
{
    c = p.get_char();
    foreground_color = p.get_foreground_color();
    background_color = p.get_background_color();
    bold = p.get_bold();
}


// This function combines pixels, element by element
// If both pixels have the same property defined, it is undefined behavior
// and the function will throw an error
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
