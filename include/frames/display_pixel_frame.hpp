#ifndef FRAMES_DISPLAY_PIXEL_FRAME_HPP_
#define FRAMES_DISPLAY_PIXEL_FRAME_HPP_

#include <vector>

#include "components/display_pixel.hpp"
#include "frames/bool_frame.hpp"
#include "frames/color_frame.hpp"
#include "frames/frame.hpp"
#include "frames/render_pixel_frame.hpp"

namespace taeto
{

class BoolFrame;    // forward include
class CharFrame;    // forward include
class ColorFrame;   // forward include
class RenderPixelFrame;     // forward include
class DisplayPixelFrame : Frame<taeto::DisplayPixel>
{
public:
    DisplayPixelFrame(const taeto::ColorFrame&);

    DisplayPixelFrame(const taeto::RenderPixelFrame&);

    taeto::ColorFrame foreground_colors();

    taeto::ColorFrame background_colors();

    taeto::BoolFrame bolds();

    taeto::BoolFrame italics();

    taeto::BoolFrame underlines();

    taeto::BoolFrame strikethroughs();
};

}   // namespace taeto

#endif  // FRAMES_DISPLAY_PIXEL_FRAME_HPP_
