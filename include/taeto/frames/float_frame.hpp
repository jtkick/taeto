#ifndef FRAMES_FLOAT_FRAME_HPP_
#define FRAMES_FLOAT_FRAME_HPP_

#include <algorithm>
#include <array>
#include <vector>

#include "lodepng.h"

#include "taeto/frames/frame.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/frames/vec4_frame.hpp"

namespace taeto
{

class DisplayPixelFrame;    // forward include
class RenderPixelFrame;     // forward include
class Vec4Frame;   // forward include
class FloatFrame : public taeto::Frame<float>
{
public:
    FloatFrame();

    FloatFrame(glm::uvec2 shape, float f = 0.0);

    FloatFrame(const FloatFrame&);

    FloatFrame(const Frame<float>&);

    ~FloatFrame() { };
};

}   // namespace taeto

#endif  // FRAMES_FLOAT_FRAME_HPP_
