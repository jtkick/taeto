#include "Frame.h"

// Constructors
Frame::Frame()
{

}

Frame::Frame(unsigned long int w, unsigned long int h)
{

    width = w;
    height = h;
    
    pixels = new pixel*[h];
    
    for (int i = 0; i < h; i++)
        pixels[i] = new pixel[w];
               
}

// Getters and setters
pixel Frame::get_pixel(long int h, long int w)
{
    // Make sure width in range
    if (w < 0 || w >= width)
        throw "Frame width index out of range.";
        
    // Make sure height in range
    if (h < 0 || h >= height)
        throw "Frame height index out of range.";
    
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

void Frame::set_pixel(long int h, long int w, pixel p)
{
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
            pixels[i][j].c = chars.at(i).at(j);
        
}
        
// Set just the colors of all pixels in frame
void Frame::set_colors(vector<vector<unsigned char>>)
{

}
        
// Set just the bold parameter of all pixels in frame
void Frame::set_bolds(vector<vector<bool>>)
{

}
