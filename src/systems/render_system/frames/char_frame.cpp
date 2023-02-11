#include "char_frame.h"

#include <fstream>
#include <iostream>

// Constructors
CharFrame::CharFrame()
{

}

CharFrame::CharFrame(unsigned long int h, unsigned long int w)
{
    // Keep dimensions for bounds checks if necessary
    height = h;
    width = w;

    // Initialize vectors with default values
    values = vector(h, vector<uint8_t>(w));
}

CharFrame::CharFrame(std::string path)
{
    // Decode png file
    std::vector<unsigned char> image;
    // unsigned int image_width, image_height;
    unsigned error = lodepng::decode(image, width, height, path);

    // Print load error
    if (error)
        std::cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    // Keep dimensions for bounds checking later
    // height = image_height;
    // width = image_width;

    // Load values into vector
    for (int i = 0; i < height; ++i)
    {
        // New row
        vector<uint8_t> row = vector<uint8_t>();

        for (int j = 0; j < width; ++j)
        {
            // Get RGBA values for pixel
            vector<unsigned char> rgb = vector<unsigned char>((image.begin() + i*width*4 + j*4),
                                                              (image.begin() + i*width*4 + j*4) + 3);

            // Just ignore the alpha channel because who cares

            // Assert that this pixel is greyscale, so we are confident in the value
            if (!std::equal(rgb.begin() + 1, rgb.end(), rgb.begin())) throw "Your Mom";

            // Since we checked that all values are the same, just use the red channel for the value
            row.push_back(rgb.at(0));
        }

        values.push_back(row);
    }
}

// Destructor
CharFrame::~CharFrame()
{

}

uint8_t& CharFrame::at(long int y, long int x)
{
    return NewFrame::at<uint8_t>(values, y, x);
}

unsigned int CharFrame::get_width()
{
    return width;
}

unsigned int CharFrame::get_height()
{
    return height;
}

void CharFrame::combine(CharFrame f,
                        unsigned int y,
                        unsigned int x,
                        bool tile_y = false,
                        bool tile_x = false,
                        bool normalize = true)
{
    values = NewFrame::combine<uint8_t>(
        values,
        height,
        width,
        f.values,
        f.height,
        f.width,
        y,
        x,
        tile_y,
        tile_x,
        normalize
    );
}

void CharFrame::print()
{
    std::cout << "{";

    for (int i = 0; i < height; ++i)
    {
        std::cout << "{";
        for (int j = 0; j < width; ++j)
        {
            std::cout << unsigned(values.at(i).at(j));
            if (j != width - 1) std::cout << ", ";
        }
        std::cout << "}";

        if (i != height - 1) std::cout << "," << std::endl << " ";
    }

    std::cout << "}";
}

std::string CharFrame::serialize()
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
            // Add row values
            s += std::to_string(values.at(i).at(j));

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