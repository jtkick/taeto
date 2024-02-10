#include "frames/vec3_frame.hpp"

#include <cassert>
#include <vector>

#include <glm/glm.hpp>
#include "lodepng.h"

#include "frames/float_frame.hpp"

namespace taeto
{

Vec3Frame::Vec3Frame()
{

}

Vec3Frame::Vec3Frame(glm::uvec2 size, glm::vec3 v)
{
    resize(size, v);
}

taeto::FloatFrame Vec3Frame::x()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).x;
    return frame;
}

void Vec3Frame::x(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).x = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame Vec3Frame::y()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).y;
    return frame;
}

void Vec3Frame::y(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).y = f.at(glm::uvec2(j, i));
}

taeto::FloatFrame Vec3Frame::z()
{
    taeto::FloatFrame frame(glm::uvec2(width(), height()));
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(glm::uvec2(j, i)) = at(glm::uvec2(j, i)).z;
    return frame;
}

void Vec3Frame::z(taeto::FloatFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(glm::uvec2(j, i)).z = f.at(glm::uvec2(j, i));
}

}   // namespace taeto
