#include "frames/display_pixel_frame.hpp"

#include <cassert>

#include <glm/glm.hpp>

#include "frames/char_frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vec4_frame.hpp"

namespace taeto
{

DisplayPixelFrame::DisplayPixelFrame()
{

}

taeto::CharFrame DisplayPixelFrame::chars()
{
    taeto::CharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).c;
    return frame;
}

void DisplayPixelFrame::chars(taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).c = f.at(glm::uvec2(j, i));
}

taeto::Vec3Frame DisplayPixelFrame::fg_colors()
{
    taeto::Vec3Frame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).fg_color;
    return frame;
}

void DisplayPixelFrame::fg_colors(taeto::Vec3Frame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).fg_color = f.at(glm::uvec2(j, i));
}

taeto::Vec3Frame DisplayPixelFrame::bg_colors()
{
    taeto::Vec3Frame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).bg_color;
    return frame;
}

void DisplayPixelFrame::bg_colors(taeto::Vec3Frame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).bg_color = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame DisplayPixelFrame::bolds()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).bold;
    return frame;
}

void DisplayPixelFrame::bolds(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).bold = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame DisplayPixelFrame::italics()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) =  at(glm::uvec2(j, i)).italic;
    return frame;
}

void DisplayPixelFrame::italics(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).italic = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame DisplayPixelFrame::underlines()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).underline;
    return frame;
}

void DisplayPixelFrame::underlines(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).underline = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame DisplayPixelFrame::strikethroughs()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).strikethrough;
    return frame;
}

void DisplayPixelFrame::strikethroughs(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).strikethrough = f.at(glm::uvec2(j, i));
}

void DisplayPixelFrame::add_string(int y, int x, std::string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        taeto::DisplayPixel& dp = at(glm::uvec2(x+i, y));
        dp.c = str.at(i);
        dp.fg_color = glm::vec3(1.0, 1.0, 1.0);
        dp.bg_color = glm::vec3(0.0, 0.0, 0.0);
    }
}

}   // namespace taeto
