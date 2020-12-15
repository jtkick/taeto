#include "Frame.h"

#include <fstream>

// Constructors
//Frame::Frame()
//{
//
//}

Frame::Frame(unsigned long int h, unsigned long int w)
{

    height = h;
    width = w;
    
    for (int i = 0; i < height; i++)
    {
        vector<Pixel> row;
        for (int j = 0; j < width; j++)
        {
            row.push_back(Pixel());
        }
        pixels.push_back(row);
    }            
    //pixels = array<array<Pixel, width>, height>;
               
}

// Destructor
Frame::~Frame()
{

}

// Getters and setters
Pixel Frame::get_pixel(long int h, long int w)
{
    // Make sure width in range
    if (w < 0 || w >= width)
        //throw "Frame width index out of range.";
        throw 1;
        
    // Make sure height in range
    if (h < 0 || h >= height)
        //throw "Frame height index out of range.";
        throw 2;
    
    return pixels[h][w];
}

unsigned long int Frame::get_width()
{
    return width;
}
        
unsigned long int Frame::get_height()
{
    return height;
}

void Frame::set_pixel(long int h, long int w, Pixel p)
{
    // Make sure width in range
    if (w < 0 || w >= width)
        //throw "Frame width index out of range.";
        throw 3;
        
    // Make sure height in range
    if (h < 0 || h >= height)
        //throw "Frame height index out of range.";
        throw 4;
        
    pixels[h][w] = p;
}
        
void Frame::set_width(unsigned long int w)
{
    width = w;
}
        
void Frame::set_height(unsigned long int h)
{
    height = h;
}
        
// Set just the characters of all pixels in frame
void Frame::set_chars(vector<string> chars)
{

    for (int i = 0; i < height; i++)

        for (int j = 0; j < width; j++)

            // Write chars character to pixel at corresponding location
            pixels[i][j].set_char(chars[i][j]);
        
}
        
// Set just the colors of all pixels in frame
void Frame::set_foreground_colors(vector<vector<Color>> color_vector)
{
    for (int i = 0; i < color_vector.size(); i++)
    
        for (int j = 0; j < color_vector[i].size(); j++)
        
            // Write color to character foreground
            pixels[i][j].set_foreground_color(color_vector[i][j]);
}
        
// Set just the bold parameter of all pixels in frame
void Frame::set_bolds(vector<vector<bool>>)
{
    throw "Method not implemented yet.";
}

void Frame::add_string(long int y, long int x, string str)
{
    for (int i = 0; i < str.length(); i++)
        pixels[y][x+i].set_char(str.at(i));
}
