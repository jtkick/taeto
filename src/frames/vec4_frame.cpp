#include "frames/vec4_frame.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "lodepng.h"

#include "frames/float_frame.hpp"

namespace taeto
{

Vec4Frame::Vec4Frame()
{
    resize(glm::uvec2(), glm::vec4());
}

Vec4Frame::Vec4Frame(glm::uvec2 shape, glm::vec4 v)
{
    resize(shape, v);
}

Vec4Frame::Vec4Frame(std::string path)
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
        std::vector<glm::vec4> row = std::vector<glm::vec4>();

        for (int j = 0; j < w; ++j)
        {
            // Begininning of this pixel in image
            int pixel_index = i*w*4 + j*4;

            // Get color values
            glm::vec4 c = glm::vec4();
            c.x = image.at(pixel_index);
            c.y = image.at(pixel_index+1);
            c.z = image.at(pixel_index+2);
            c.w = image.at(pixel_index+3);

            // Add pixel to our color frame
            row.push_back(c);
        }

        values_.push_back(row);
    }
}

taeto::FloatFrame Vec4Frame::x()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).x;
    return frame;
}

// const taeto::FloatFrame& Vec4Frame::x() const
// {
//     std::function<unsigned char(glm::vec4)> func =
//         [](glm::vec4 c){ return c.x; };
//     return taeto::FloatFrame(extract_member_frame<unsigned char>(func));
// }

void Vec4Frame::x(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).x = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame Vec4Frame::y()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).y;
    return frame;
}

void Vec4Frame::y(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).y = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame Vec4Frame::z()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).z;
    return frame;
}

void Vec4Frame::z(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).z = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame Vec4Frame::w()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).w;
    return frame;
}

void Vec4Frame::w(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).w = f.at(glm::uvec2(j, i));
}

}   // namespace taeto
