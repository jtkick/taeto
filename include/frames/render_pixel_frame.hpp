#ifndef FRAMES_RENDER_PIXEL_FRAME_H_
#define FRAMES_RENDER_PIXEL_FRAME_H_

#include <vector>

#include "components/display_pixel.hpp"
#include "frames/color_frame.hpp"
#include "frames/frame.hpp"

namespace taeto
{

class RenderPixelFrame : Frame<taeto::DisplayPixel>
{
public:
    RenderPixelFrame(const taeto::ColorFrame&);

    RenderPixelFrame(const taeto::RenderPixelFrame&);

    taeto::ColorFrame foreground_colors();

    taeto::ColorFrame background_colors();
};

}   // namespace taeto

#endif  // FRAMES_RENDER_PIXEL_FRAME_H_
