#include "frames/color_frame.hpp"

#include "components/color.hpp"
#include "frames/uchar_frame.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "lodepng.h"

namespace taeto
{

ColorFrame::ColorFrame()
{
    resize(0, 0, taeto::Color());
}

ColorFrame::ColorFrame(
    unsigned long int h, unsigned long int w, taeto::Color c)
{
    resize(h, w, c);
}

ColorFrame::ColorFrame(std::string path)
{
    // Decode png file
    unsigned int h, w = 0;
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
        std::vector<taeto::Color> row = std::vector<taeto::Color>();

        for (int j = 0; j < w; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*w*4 + j*4;

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

taeto::UCharFrame ColorFrame::reds()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).red;
    return frame;
}

// const taeto::UCharFrame& ColorFrame::reds() const
// {
//     std::function<unsigned char(taeto::Color)> func =
//         [](taeto::Color c){ return c.red; };
//     return taeto::UCharFrame(extract_member_frame<unsigned char>(func));
// }

void ColorFrame::reds(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).red = f.at(i, j);
}

taeto::UCharFrame ColorFrame::greens()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).green;
    return frame;
}

void ColorFrame::greens(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).green = f.at(i, j);
}

taeto::UCharFrame ColorFrame::blues()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).blue;
    return frame;
}

void ColorFrame::blues(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).blue = f.at(i, j);
}

taeto::UCharFrame ColorFrame::alphas()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).alpha;
    return frame;
}

void ColorFrame::alphas(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).alpha = f.at(i, j);
}

}   // namespace taeto
