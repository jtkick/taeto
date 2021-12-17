#include "Frame.h"

#include <fstream>
#include <iostream>

// Constructors
Frame::Frame()
{

}

Frame::Frame(unsigned long int h, unsigned long int w)
{

    height = h;
    width = w;

    init_pixels();

}

Frame::Frame(std::vector<std::vector<Pixel>> p)
{
    height = p.size();

    // Ensure all rows are the same length
    // I guess you can initialize with no height, just promise to be safe
    if (height > 0)
    {
        width = p.at(0).size();
        for (int i = 1; i < p.size(); i++)
        {
            if (p.at(i).size() != width)
            {
                throw "I will literally shit yourself.";
            }
        }
    }

    pixels = p;
}

// Destructor
Frame::~Frame()
{

}

// Init pixels vectors
void Frame::init_pixels()
{
    for (int i = 0; i < height; i++)
    {
        vector<Pixel> row;
        for (int j = 0; j < width; j++)
        {
            row.push_back(Pixel());
        }
        pixels.push_back(row);
    }
}

// Getters and setters
Pixel& Frame::get_pixel(long int h, long int w)
{
    return pixels.at(h).at(w);
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
    // Only update dimensions if they changed, becuase it expensive
    if (w != width)
    {
        width = w;
        init_pixels();
    }
}

void Frame::set_height(unsigned long int h)
{
    // Only update dimensions if they changed, becuase it expensive
    if (h != height)
    {
        height = h;
        init_pixels();
    }
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

// Set just the colors of all pixels in frame
void Frame::set_background_colors(vector<vector<Color>> color_vector)
{
    for (int i = 0; i < color_vector.size(); i++)

        for (int j = 0; j < color_vector[i].size(); j++)

            // Write color to character foreground
            pixels[i][j].set_background_color(color_vector[i][j]);
}

// Set just the bold parameter of all pixels in frame
void Frame::set_bolds(vector<vector<bool>>)
{
    throw "Method not implemented yet.";
}

// Set just the normal vector parameter of all pixels in frame
void Frame::set_normals(vector<vector<Vector>> normals) // Ah yes, the vector<vector<Vector>>.
{
    for (int i = 0; i < normals.size(); i++)

        for (int j = 0; j < normals[i].size(); j++)

            pixels[i][j].set_normal(normals[i][j]);
}

// Set just the normal vector parameter of single pixel in frame
void set_normal(unsigned long int, unsigned long int, Vector normal)
{

}

void Frame::add_string(long int y, long int x, string str)
{
    Color white = Color(255, 255, 255, 255);
    Color black = Color(0, 0, 0, 255);

    for (int i = 0; i < str.length(); i++)
        pixels[y][x+i] = Pixel(str.at(i), white, black, false);
}

std::string Frame::serialize()
{
    std::string s = "";

    // Open frame
    s += "{";

    // Open pixels vector
    s += "{";

    for (int i = 0; i < height; i++)
    {
        // Open row vector
        s += "{";

        for (int j = 0; j < width; j++)
        {
            // Add row pixels
            s += pixels.at(i).at(j).serialize();

            if (i != height - 1)
            {
                s += ",";
            }
        }

        // Close row vector
        s += "}";

        if (i != height - 1)
        {
            s += ",";
        }

    }

    // Close pixels vector
    s += "}";

    // Close frame
    s += "}";

    return s;
}
