#include "frames/vector_frame.hpp"

#include "components/vector.hpp"
#include "frames/uchar_frame.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "lodepng.h"

namespace taeto
{

VectorFrame::VectorFrame()
{

}

taeto::UCharFrame VectorFrame::x()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).x();
    return frame;
}

void VectorFrame::x(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).x(f.at(i, j));
}

taeto::UCharFrame VectorFrame::y()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).y();
    return frame;
}

void VectorFrame::y(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).y(f.at(i, j));
}

taeto::UCharFrame VectorFrame::z()
{
    taeto::UCharFrame frame(height(), width());
    for (int i = 0; i < frame.height(); ++i)
        for (int j = 0; j < frame.width(); ++j)
            frame.at(i, j) = at(i, j).z();
    return frame;
}

void VectorFrame::z(taeto::UCharFrame& f)
{
    assert(height() == f.height());
    assert(width() == f.width());
    for (int i = 0; i < height(); ++i)
        for (int j = 0; j < width(); ++j)
            at(i, j).z(f.at(i, j));
}

}   // namespace taeto
