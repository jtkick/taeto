#include "pre_lighting_pass_frame.h"

#include <fstream>
#include <iostream>

// Constructors
PreLightingPassFrame::PreLightingPassFrame()
{

}

PreLightingPassFrame::PreLightingPassFrame(unsigned long int h, unsigned long int w, int max_pixel_depth)
{
    // Keep dimensions for bounds checks if necessary
    height = h;
    width = w;

    // Initialize vectors with default values
    // values = vector(h, vector<PreLightingPassPixel>(w));
    values = vector(h, vector(w, vector<PreLightingPassPixel>(max_pixel_depth)));

    // Set each pixel stack's size to prevent constant resizing
    // for (vector<vector<PreLightingPassPixel>> row : values)
    //     for (vector<PreLightingPassPixel> pixel_stack : row)
    //         pixel_stack.reserve(max_pixel_depth);

    // TODO: MAKE SURE RENDER SYSTEM DOESN'T GO OVER THE END OF THE PIXEL STACK

}

// Destructor
PreLightingPassFrame::~PreLightingPassFrame()
{

}

std::vector<PreLightingPassPixel>& PreLightingPassFrame::at(long int y, long int x)
{
    return NewFrame::at<std::vector<PreLightingPassPixel>>(values, y, x);
}

std::string PreLightingPassFrame::serialize()
{
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
    //         s += std::to_string(values.at(i).at(j));
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
