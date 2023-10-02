#include "frames/uchar_frame.hpp"

#include <fstream>
#include <iostream>

namespace taeto
{

UCharFrame::UCharFrame()
{
    resize(0, 0, 0);
}

UCharFrame::UCharFrame(unsigned long int h, unsigned long int w, uint8_t v)
{
    resize(h, w, v);
}

// UCharFrame::UCharFrame(
//     const taeto::ColorFrame& cf, std::string method = "luminosity")
// {
//     for (int y = 0; y < height(); ++y)
//     {
//         for (int x = 0; x < width(); ++x)
//         {
//             const taeto::Color& curr_color = at(y, x);
//             if (method == "luminosity")
//                 values_.at(y, x) =
//                     0.30 * curr_color.red() +
//                     0.59 * curr_color.green() +
//                     0.11 * curr_color.blue();
//             else if (method == "average")
//                 values_.at(y, x) =
//                     ((uint16_t)curr_color.red() +
//                      (uint16_t)curr_color.green() +
//                      (uint16_t)curr_color.blue()) /
//                     3;
//             else
//                 throw std::exception("Unknown conversion method.");
//         }
//     }
// }

UCharFrame::UCharFrame(const taeto::Frame<unsigned char>& f)
{
    values_ = f.values_;
}

}   // namespace taeto
