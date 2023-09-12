#include "frames/vector_frame.hpp"

#include "components/vector.hpp"
#include "frames/uchar_frame.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "lodepng.h"

namespace taeto
{

VectorFrame::VectorFrame()
{

}

const taeto::UCharFrame& VectorFrame::x() const
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).x;
    return frame;
}

void VectorFrame::x(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).x = f.at(i, j);
}

const taeto::UCharFrame& VectorFrame::y() const
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).y;
    return frame;
}

void VectorFrame::y(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).y = f.at(i, j);
}

const taeto::UCharFrame& VectorFrame::z() const
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = values_.at(i, j).z;
    return frame;
}

void VectorFrame::z(const taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            values_.at(i, j).z = f.at(i, j);
}

}   // namespace taeto
