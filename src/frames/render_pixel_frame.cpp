#include "frames/render_pixel_frame.hpp"

#include <cassert>

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "frames/char_frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vec3_frame.hpp"
#include "frames/vec4_frame.hpp"

namespace taeto
{

RenderPixelFrame::RenderPixelFrame()
{

}

taeto::CharFrame RenderPixelFrame::chars()
{
    taeto::CharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).c;
    return frame;
}

void RenderPixelFrame::chars(taeto::CharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).c = f.at(glm::uvec2(j, i));
}

taeto::Vec4Frame RenderPixelFrame::fg_colors()
{
    taeto::Vec4Frame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).fg_color;
    return frame;
}

void RenderPixelFrame::fg_colors(taeto::Vec4Frame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).fg_color = f.at(glm::uvec2(j, i));
}

taeto::Vec4Frame RenderPixelFrame::bg_colors()
{
    taeto::Vec4Frame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).bg_color;
    return frame;
}

void RenderPixelFrame::bg_colors(taeto::Vec4Frame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).bg_color = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame RenderPixelFrame::bolds()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)), at(glm::uvec2(j, i)).bold;
    return frame;
}

void RenderPixelFrame::bolds(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).bold = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame RenderPixelFrame::italics()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).italic;
    return frame;
}

void RenderPixelFrame::italics(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).italic = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame RenderPixelFrame::underlines()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)), at(glm::uvec2(j, i)).underline;
    return frame;
}

void RenderPixelFrame::underlines(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).underline = f.at(glm::uvec2(j, i));
}

taeto::UCharFrame RenderPixelFrame::strikethroughs()
{
    taeto::UCharFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).strikethrough;
    return frame;
}

void RenderPixelFrame::strikethroughs(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).strikethrough = f.at(glm::uvec2(j, i));
}

taeto::Vec3Frame RenderPixelFrame::normals()
{
    taeto::Vec3Frame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).normal;
    return frame;
}

void RenderPixelFrame::normals(taeto::Vec3Frame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).normal = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame RenderPixelFrame::specularities()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).specularity;
    return frame;
}

void RenderPixelFrame::specularities(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).specularity = f.at(glm::uvec2(j, i));
}

}   // namespace taeto
