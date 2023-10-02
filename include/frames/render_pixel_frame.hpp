#ifndef FRAMES_RENDER_PIXEL_FRAME_HPP_
#define FRAMES_RENDER_PIXEL_FRAME_HPP_

#include "components/render_pixel.hpp"
#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vector_frame.hpp"
#include "frames/frame.hpp"

namespace taeto
{

// Forward includes
class BoolFrame;
class CharFrame;
class ColorFrame;
class UCharFrame;
class VectorFrame;

class RenderPixelFrame : Frame<taeto::RenderPixel>
{
public:
    RenderPixelFrame();

    RenderPixelFrame(const taeto::ColorFrame&);

    RenderPixelFrame(const taeto::RenderPixelFrame&);

    ~RenderPixelFrame() { };

    taeto::CharFrame chars();

    void chars(taeto::CharFrame&);

    taeto::ColorFrame foreground_colors();

    void foreground_colors(taeto::ColorFrame&);

    taeto::ColorFrame background_colors();

    void background_colors(taeto::ColorFrame&);

    taeto::BoolFrame bolds();

    void bolds(taeto::BoolFrame&);

    taeto::BoolFrame italics();

    void italics(taeto::BoolFrame&);

    taeto::BoolFrame underlines();

    void underlines(taeto::BoolFrame&);

    taeto::BoolFrame strikethroughs();

    void strikethroughs(taeto::BoolFrame&);

    taeto::VectorFrame normals();

    void normals(taeto::VectorFrame&);

    taeto::UCharFrame specularities();

    void specularities(taeto::UCharFrame&);
};

}   // namespace taeto

#endif  // FRAMES_RENDER_PIXEL_FRAME_HPP_
