#include "frames/uchar_frame.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "lodepng.h"

namespace taeto
{

UCharFrame::UCharFrame()
{

}

UCharFrame::UCharFrame(glm::uvec2 shape, unsigned char c)
{
    resize(shape, c);
}

UCharFrame::UCharFrame(std::string path)
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
        std::vector<unsigned char> row = std::vector<unsigned char>();

        for (int j = 0; j < w; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*w*4 + j*4;

            if (image.at(pixel_index == 255) &&
                image.at(pixel_index+1 == 255) &&
                image.at(pixel_index+2 == 255))
                row.push_back(1);
            else if (image.at(pixel_index == 0) &&
                     image.at(pixel_index+1 == 0) &&
                     image.at(pixel_index+2 == 0))
                row.push_back(0);
            else
                throw std::runtime_error(
                    "Expected fully black or fully white pixels.");
        }

        values_.push_back(row);
    }
}

}   // namespace taeto
