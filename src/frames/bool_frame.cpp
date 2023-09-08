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

BoolFrame::BoolFrame(std::string path)
{
    // Decode png file
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, path);

    // Print load error
    if (error)
        std::cerr << "PNG decoder error " << error << ": "
                  << lodepng_error_text(error) << std::endl;

    // Load values into vector
    for (int i = 0; i < height; ++i)
    {
        // New row
        std::vector<taeto::bool> row = std::vector<taeto::bool>();

        for (int j = 0; j < width; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*width*4 + j*4;

            if (image.at(pixel_index == 255) &&
                image.at(pixel_index+1 == 255) &&
                image.at(pixel_index+2 == 255))
                row.push_back(true);
            else if (image.at(pixel_index == 0) &&
                     image.at(pixel_index+1 == 0) &&
                     image.at(pixel_index+2 == 0))
                row.push_back(false);
            else
                throw Exception("Expected fully black or fully white pixels.");
        }

        values_.push_back(row);
    }
}

}   // namespace taeto
