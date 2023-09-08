#ifndef FRAMES_COLOR_FRAME_HPP_
#define FRAMES_COLOR_FRAME_HPP_

#include "components/color.hpp"
#include "frames/frame.hpp"
#include "frames/uchar_frame.hpp"

namespace taeto
{

class UCharFrame;   // forward include
class ColorFrame : Frame<taeto::Color>
{
public:
    ColorFrame();

    ColorFrame(std::string path);

    ~ColorFrame();

    taeto::UCharFrame to_black_and_white(std::string);
};

}   // namespace taeto

#endif  // FRAMES_COLOR_FRAME_HPP_
