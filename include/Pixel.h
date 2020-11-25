#ifndef STRUCTS
#define STRUCTS

#include <vector>

class Pixel
{
    private:
    
        // Actual character to print
        char c = '\0';
    
        // Color of this 'pixel'
        // Based on whatever color palette is set in the engine
        // Negative is "don't care", i.e. the pixel is the color of whatever is behind this pixel
        int16_t foreground_color = -1;
        
        // Color of background of 'pixel'
        // Negative is "don't care", i.e. the background is the color of whatever is behind this pixel
        int16_t background_color = -1;
 
        // Whether this 'pixel' should be printed in bold
        // 0 is false, 1 is true, negative is "don't care"
        int8_t bold = -1;
        
    public:
    
        // Constructors
        Pixel();
        
        Pixel(char, int16_t, int16_t, int8_t);
        
        // Getters and setters
        char get_char();
        
        int16_t get_foreground_color();
        
        int16_t get_background_color();
        
        int8_t get_bold();
        
        void set_char(char);
        
        void set_foreground_color(int16_t);
        
        void set_background_color(int16_t);
        
        void set_bold(int8_t);
};


Pixel::Pixel()
{

}


Pixel::Pixel(char, int16_t, int16_t, int8_t);
        
// Getters and setters
char Pixel::get_char()
{
    return c;
}

        
int16_t Pixel::get_foreground_color()
{
    return foreground_color;
}

        
int16_t Pixel::get_background_color()
{
    return background_color;
}

        
int8_t Pixel::get_bold()
{
    return bold;
}

        
void Pixel::set_char(char new_char)
{
    c = new_char;
}

        
void Pixel::set_foreground_color(int16_t color)
{
    foreground_color = color;
}
        
void Pixel::set_background_color(int16_t color)
{
    background_color = color;
}
        
void Pixel::set_bold(int8_t b)
{
    bold = b;
}

    
bool operator == (const Pixel& p1, const Pixel& p2)
{
    return (p1.c == p2.c &&
            p1.foreground_color == p2.foreground_color &&
            p1.background_color == p2.background_color &&
            p1.bold == p2.bold);
}


void Pixel::operator = (const Pixel &p)
{
    c = p.c;
    foreground_color = p.foreground_color;
    background_color = p.background_color;
    bold = p.bold;
}


// This function combines pixels, element by element
// If both pixels have the same property defined, it is undefined behavior
// and the function will throw an error
void Pixel::operator + (const Pixel &p)
{
    // Combine char
    if (c >= 0 && p.c < 0)
        ; // no-op
    else if (c < 0 && p.c >= 0)
        c = p.c;
    else if (c < 0 && p.c < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both characters defined.";
        
    // Combine foreground color
    if (foreground_color >= 0 && p.foreground_color < 0)
        ; // no-op
    else if (foreground_color < 0 && p.foreground_color >= 0)
        foreground_color = p.foreground_color;
    else if (foreground_color < 0 && p.foreground_color < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both foreground colors defined.";
        
    // Combine background color
    if (background_color >= 0 && p.background_color < 0)
        ; // no-op
    else if (background_color < 0 && p.background_color >= 0)
        background_color = p.background_color;
    else if (background_color < 0 && p.background_color < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both background colors defined.";
        
    // Combine bold property
    if (bold >= 0 && p.bold < 0)
        ; // no-op
    else if (bold < 0 && p.bold >= 0)
        bold = p.bold;
    else if (bold < 0 && p.bold < 0)
        ; // no-op
    else
        throw "Cannot combine pixels: both bold properties defined.";
        
}
        


#endif
