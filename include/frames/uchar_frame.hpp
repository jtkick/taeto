#ifndef FRAMES_UCHAR_FRAME_HPP_
#define FRAMES_UCHAR_FRAME_HPP_

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
class UCharFrame : Frame<uint8_t>
{
public:
    UCharFrame();

    UCharFrame(unsigned long int, unsigned long int);

    UCharFrame(const UCharFrame&);

    UCharFrame(const Frame<unsigned char>&);

    // Conversion constructors
    UCharFrame(const taeto::ColorFrame& cf);

    UCharFrame(const DisplayPixelFrame&);

    UCharFrame(const RenderPixelFrame&);

    ~UCharFrame();
};

}   // namespace taeto

#endif  // FRAMES_UCHAR_FRAME_HPP_
