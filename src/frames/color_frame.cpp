#include "frames/color_frame.hpp"

#include "components/color.hpp"
#include "frames/uchar_frame.hpp"

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

const taeto::UCharFrame& ColorFrame::reds() const
{
    std::function<unsigned char(taeto::Color)> func =
        [](taeto::Color c){ return c.red; };
    return extract_member_frame<unsigned char>(func);
}

void ColorFrame::reds(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).red = f.at(i, j);
}

const taeto::UCharFrame& ColorFrame::greens() const
{
    std::function<unsigned char(taeto::Color)> func =
        [](taeto::Color c){ return c.green; };
    return extract_member_frame<unsigned char>(func);
}

void ColorFrame::greens(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).green = f.at(i, j);
}

const taeto::UCharFrame& ColorFrame::blues() const
{
    std::function<unsigned char(taeto::Color)> func =
        [](taeto::Color c){ return c.blue; };
    return extract_member_frame<unsigned char>(func);
}

void ColorFrame::blues(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).blue = f.at(i, j);
}

const taeto::UCharFrame& ColorFrame::alphas() const
{
    std::function<unsigned char(taeto::Color)> func =
        [](taeto::Color c){ return c.alpha; };
    return extract_member_frame<unsigned char>(func);
}

void ColorFrame::alphas(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).alpha = f.at(i, j);
}

}   // namespace taeto
