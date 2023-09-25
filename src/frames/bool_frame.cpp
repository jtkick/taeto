#include "frames/bool_frame.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include "lodepng.h"

namespace taeto
{

BoolFrame::BoolFrame()
{

}

BoolFrame::BoolFrame(unsigned long int h, unsigned long int w, bool b)
{
    resize(h, w, b);
}

BoolFrame::BoolFrame(std::string path)
{
    // Decode png file
    unsigned int w, h = 0;
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, w, h, path);

    // Print load error
    if (error)
        std::cerr << "PNG decoder error " << error << ": "
                  << lodepng_error_text(error) << std::endl;

    // Load values into vector
    for (int i = 0; i < h; ++i)
    {
        // New row
        std::vector<bool> row = std::vector<bool>();

        for (int j = 0; j < w; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*w*4 + j*4;

            if (image.at(pixel_index == 255) &&
                image.at(pixel_index+1 == 255) &&
                image.at(pixel_index+2 == 255))
                row.push_back(true);
            else if (image.at(pixel_index == 0) &&
                     image.at(pixel_index+1 == 0) &&
                     image.at(pixel_index+2 == 0))
                row.push_back(false);
            else
                throw std::runtime_error(
                    "Expected fully black or fully white pixels.");
        }

        values_.push_back(row);
    }
}

}   // namespace taeto
