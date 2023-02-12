#include "systems/render_system/color_frame.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include "components/color.h"

namespace taeto
{

ColorFrame::ColorFrame()
{

}

ColorFrame::ColorFrame(unsigned long int h, unsigned long int w)
{
    // Keep dimensions for bounds checks if necessary
    height = h;
    width = w;

    // Initialize vectors with default values
    values = std::vector(h, std::vector<taeto::Color>(w));
}

ColorFrame::ColorFrame(std::string path)
{
    // Decode png file
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, path);

    // Print load error
    if (error)
        std::cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    // Load values into vector
    for (int i = 0; i < height; ++i)
    {
        // New row
        std::vector<taeto::Color> row = std::vector<taeto::Color>();

        for (int j = 0; j < width; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*width*4 + j*4;

            // Get color values
            taeto::Color c = taeto::Color();
            c.red = image.at(pixel_index);
            c.green = image.at(pixel_index+1);
            c.blue = image.at(pixel_index+2);
            c.alpha = image.at(pixel_index+3);

            // Add pixel to our color frame
            row.push_back(c);
        }

        values.push_back(row);
    }
}

ColorFrame::~ColorFrame()
{

}

taeto::Color& ColorFrame::at(long int y, long int x)
{
    return NewFrame::at<taeto::Color>(values, y, x);
}

unsigned int ColorFrame::get_width()
{
    return width;
}

unsigned int ColorFrame::get_height()
{
    return height;
}

void ColorFrame::combine(ColorFrame f,
                        unsigned int y,
                        unsigned int x,
                        bool tile_y = false,
                        bool tile_x = false,
                        bool normalize = true)
{
    values = NewFrame::combine<taeto::Color>(
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

void ColorFrame::print()
{
    throw "not implemented";

    // std::cout << "{";
    //
    // for (int i = 0; i < height; ++i)
    // {
    //     std::cout << "{";
    //     for (int j = 0; j < width; ++j)
    //     {
    //         std::cout << values.at(i).at(j);
    //         if (j != width - 1) std::cout << ", ";
    //     }
    //     std::cout << "}";
    //
    //     if (i != height - 1) std::cout << "," << std::endl << " ";
    // }
    //
    // std::cout << "}";
}

std::string ColorFrame::serialize()
{
    throw "not implemented";
    //
    // std::string s = "";
    //
    // // Open frame
    // s += "{";
    //
    // // Open pixels vector
    // s += "{";
    //
    // for (int i = 0; i < height; i++)
    // {
    //     // Open row vector
    //     s += "{";
    //
    //     for (int j = 0; j < width; j++)
    //     {
    //         // Add row values
    //         s += std::to_string(values.at(i, j));
    //
    //         if (i != height - 1)
    //         {
    //             s += ",";
    //         }
    //     }
    //
    //     // Close row vector
    //     s += "}";
    //
    //     if (i != height - 1)
    //     {
    //         s += ",";
    //     }
    //
    // }
    //
    // // Close pixels vector
    // s += "}";
    //
    // // Close frame
    // s += "}";
    //
    // return s;
}

taeto::Sprite ColorFrame::to_sprite()
{
    // Create sprite of this size

}

}   // namespace taeto
