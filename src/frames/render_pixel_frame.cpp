#include "frames/render_pixel_frame.hpp"

#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vector_frame.hpp"

#include <cassert>

namespace taeto
{

RenderPixelFrame::RenderPixelFrame()
{

}

taeto::CharFrame RenderPixelFrame::chars()
{
    taeto::CharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).c;
    return frame;
}

void RenderPixelFrame::chars(taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).c = f.at(i, j);
}

taeto::ColorFrame RenderPixelFrame::foreground_colors()
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).foreground_color;
    return frame;
}

void RenderPixelFrame::foreground_colors(taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).foreground_color = f.at(i, j);
}

taeto::ColorFrame RenderPixelFrame::background_colors()
{
    taeto::ColorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).background_color;
    return frame;
}

void RenderPixelFrame::background_colors(taeto::ColorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).background_color = f.at(i, j);
}

taeto::BoolFrame RenderPixelFrame::bolds()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).bold);
    return frame;
}

void RenderPixelFrame::bolds(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).bold = f.at(i, j);
}

taeto::BoolFrame RenderPixelFrame::italics()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).italic);
    return frame;
}

void RenderPixelFrame::italics(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).italic = f.at(i, j);
}

taeto::BoolFrame RenderPixelFrame::underlines()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).underline);
    return frame;
}

void RenderPixelFrame::underlines(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).underline = f.at(i, j);
}

taeto::BoolFrame RenderPixelFrame::strikethroughs()
{
    taeto::BoolFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.set(i, j, at(i, j).strikethrough);
    return frame;
}

void RenderPixelFrame::strikethroughs(taeto::BoolFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).strikethrough = f.at(i, j);
}

taeto::VectorFrame RenderPixelFrame::normals()
{
    taeto::VectorFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).normal;
    return frame;
}

void RenderPixelFrame::normals(taeto::VectorFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).normal = f.at(i, j);
}

taeto::UCharFrame RenderPixelFrame::specularities()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).specularity;
    return frame;
}

void RenderPixelFrame::specularities(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).specularity = f.at(i, j);
}

}   // namespace taeto
