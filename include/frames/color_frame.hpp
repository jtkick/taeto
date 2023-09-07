#ifndef FRAMES_COLOR_FRAME_H_
#define FRAMES_COLOR_FRAME_H_

#include "components/color.hpp"
#include "frames/frame.hpp"

namespace taeto
{

class ColorFrame : Frame<taeto::Color>
{
public:
    ColorFrame();

    ColorFrame(std::string path);

    ~ColorFrame();

    taeto::UCharFrame to_black_and_white(std::string);
};

}   // namespace taeto

#endif  // FRAMES_COLOR_FRAME_H_
