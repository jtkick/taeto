#ifndef FRAMES_CHAR_FRAME_HPP_
#define FRAMES_CHAR_FRAME_HPP_

#include <algorithm>
#include <array>
#include <vector>

#include "lodepng.h"

#include "frames/frame.hpp"
#include "frames/render_pixel_frame.hpp"

namespace taeto
{

class DisplayPixelFrame;    // forward include
class RenderPixelFrame;     // forward include
class CharFrame : public taeto::Frame<char>
{
public:
    CharFrame();

    CharFrame(glm::uvec2 shape, char c = ' ');

    CharFrame(const CharFrame&);

    // Conversion constructors
    CharFrame(const taeto::DisplayPixelFrame&);

    CharFrame(const taeto::RenderPixelFrame&);

    ~CharFrame() { };
};

}   // namespace taeto

#endif  // FRAMES_UCHAR_FRAME_HPP_
