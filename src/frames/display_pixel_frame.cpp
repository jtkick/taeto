#include "frames/display_pixel_frame.hpp"

#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"

namespace taeto
{

DisplayPixelFrame::DisplayPixelFrame()
{

}

const taeto::CharFrame& DisplayPixelFrame::chars() const
{
    taeto::CharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).char;
    return frame;
}

void DisplayPixelFrame::chars(const taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).char = f.at(i, j);
}

const taeto::ColorFrame& DisplayPixelFrame::foreground_colors() const
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).foreground_color;
    return frame;
}

void DisplayPixelFrame::foreground_colors(const taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).foreground_color = f.at(i, j);
}

const taeto::ColorFrame& DisplayPixelFrame::background_colors() const
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).background_color;
    return frame;
}

void DisplayPixelFrame::background_colors(const taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).background_color = f.at(i, j);
}

const taeto::BoolFrame& DisplayPixelFrame::bolds() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).bold;
    return frame;
}

void DisplayPixelFrame::bolds(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).bold = f.at(i, j);
}

const taeto::BoolFrame& DisplayPixelFrame::italics() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).italic;
    return frame;
}

void DisplayPixelFrame::italics(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).italic = f.at(i, j);
}

const taeto::BoolFrame& DisplayPixelFrame::underlines() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).underline;
    return frame;
}

void DisplayPixelFrame::underlines(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).underline = f.at(i, j);
}

const taeto::BoolFrame& DisplayPixelFrame::strikethroughs() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).strikethrough;
    return frame;
}

void DisplayPixelFrame::strikethroughs(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).strikethrough = f.at(i, j);
}

void DisplayPixelFrame::add_string(int y, int x, std::string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        taeto::DisplayPixel& dp = at(y, x+i);
        dp.char = str.at(i);
        dp.foreground_color = taeto::Color(255, 255, 255, 255);
        dp.background_color = taeto::Color(0, 0, 0, 255);
    }
}

}   // namespace taeto
