#include "systems/render_system/color_frame.hpp"

#include "components/color.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "lodepng.h"

namespace taeto
{

ColorFrame::ColorFrame()
{

}

ColorFrame::ColorFrame(std::string path)
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

        values_.push_back(row);
    }
}

}   // namespace taeto
