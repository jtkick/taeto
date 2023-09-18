#ifndef FRAMES_CHAR_FRAME_HPP_
#define FRAMES_CHAR_FRAME_HPP_

#include <algorithm>
#include <array>
#include <vector>

#include "lodepng.h"

#include "frames/color_frame.hpp"
#include "frames/frame.hpp"
#include "frames/render_pixel_frame.hpp"

namespace taeto
{

class ColorFrame;   // forward include
class DisplayPixelFrame;    // forward include
class RenderPixelFrame;     // forward include
class CharFrame : public Frame<uint8_t>
{
public:
    CharFrame();

    CharFrame(unsigned long int, unsigned long int);

    CharFrame(const CharFrame&);

    // Conversion constructors
    CharFrame(const taeto::ColorFrame& cf);

    CharFrame(const DisplayPixelFrame&);

    CharFrame(const RenderPixelFrame&);

    ~CharFrame();
};

}   // namespace taeto

#endif  // FRAMES_UCHAR_FRAME_HPP_
