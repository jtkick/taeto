#include "frames/display_pixel_frame.hpp"

#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"

#include <cassert>

namespace taeto
{

DisplayPixelFrame::DisplayPixelFrame()
{

}

taeto::CharFrame DisplayPixelFrame::chars()
{
    taeto::CharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).c;
    return frame;
}

void DisplayPixelFrame::chars(taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).c = f.at(i, j);
}

taeto::ColorFrame DisplayPixelFrame::foreground_colors()
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).foreground_color;
    return frame;
}

void DisplayPixelFrame::foreground_colors(taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).foreground_color = f.at(i, j);
}

taeto::ColorFrame DisplayPixelFrame::background_colors()
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).background_color;
    return frame;
}

void DisplayPixelFrame::background_colors(taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).background_color = f.at(i, j);
}

taeto::BoolFrame DisplayPixelFrame::bolds()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).bold);
    return frame;
}

void DisplayPixelFrame::bolds(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).bold = f.at(i, j);
}

taeto::BoolFrame DisplayPixelFrame::italics()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).italic);
    return frame;
}

void DisplayPixelFrame::italics(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).italic = f.at(i, j);
}

taeto::BoolFrame DisplayPixelFrame::underlines()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).underline);
    return frame;
}

void DisplayPixelFrame::underlines(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).underline = f.at(i, j);
}

taeto::BoolFrame DisplayPixelFrame::strikethroughs()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).strikethrough);
    return frame;
}

void DisplayPixelFrame::strikethroughs(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).strikethrough = f.at(i, j);
}

void DisplayPixelFrame::add_string(int y, int x, std::string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        taeto::DisplayPixel& dp = at(y, x+i);
        dp.c = str.at(i);
        dp.foreground_color = taeto::Color(255, 255, 255, 255);
        dp.background_color = taeto::Color(0, 0, 0, 255);
    }
}

}   // namespace taeto
