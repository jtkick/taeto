#ifndef FRAMES_DISPLAY_PIXEL_FRAME_H_
#define FRAMES_DISPLAY_PIXEL_FRAME_H_

#include <vector>

#include "components/display_pixel.hpp"
#include "frames/frame.hpp"

namespace taeto
{

class DisplayPixelFrame : Frame<taeto::DisplayPixel>
{
public:
    DisplayPixelFrame(const taeto::ColorFrame&);

    DisplayPixelFrame(const taeto::RenderPixelFrame&);

    taeto::CharFrame chars();

    taeto::ColorFrame foreground_colors();

    taeto::ColorFrame background_colors();

    taeto::BoolFrame bolds();

    taeto::BoolFrame italics();

    taeto::BoolFrame underlines();

    taeto::BoolFrame strikethroughs();
};

}   // namespace taeto

#endif  // FRAMES_DISPLAY_PIXEL_FRAME_H_
