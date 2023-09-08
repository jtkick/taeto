#include "frames/render_pixel_frame.hpp"

#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vector_frame.hpp"

namespace taeto
{

RenderPixelFrame::RenderPixelFrame()
{

}

const taeto::CharFrame& RenderPixelFrame::chars() const
{
    taeto::CharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).char;
    return frame;
}

void RenderPixelFrame::chars(const taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).char = f.at(i, j);
}

const taeto::ColorFrame& RenderPixelFrame::foreground_colors() const
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).foreground_color;
    return frame;
}

void RenderPixelFrame::foreground_colors(const taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).foreground_color = f.at(i, j);
}

const taeto::ColorFrame& RenderPixelFrame::background_colors() const
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).background_color;
    return frame;
}

void RenderPixelFrame::background_colors(const taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).background_color = f.at(i, j);
}

const taeto::BoolFrame& RenderPixelFrame::bolds() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).bold;
    return frame;
}

void RenderPixelFrame::bolds(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).bold = f.at(i, j);
}

const taeto::BoolFrame& RenderPixelFrame::italics() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).italic;
    return frame;
}

void RenderPixelFrame::italics(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).italic = f.at(i, j);
}

const taeto::BoolFrame& RenderPixelFrame::underlines() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).underline;
    return frame;
}

void RenderPixelFrame::underlines(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).underline = f.at(i, j);
}

const taeto::BoolFrame& RenderPixelFrame::strikethroughs() const
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).strikethrough;
    return frame;
}

void RenderPixelFrame::strikethroughs(const taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).strikethrough = f.at(i, j);
}

const taeto::VectorFrame& RenderPixelFrame::normals() const
{
    taeto::VectorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).normal;
    return frame;
}

void RenderPixelFrame::normals(const taeto::VectorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).normal = f.at(i, j);
}

const taeto::UCharFrame& RenderPixelFrame::specularities() const
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).specularity;
    return frame;
}

void RenderPixelFrame::specularities(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).specularity = f.at(i, j);
}

}   // namespace taeto
