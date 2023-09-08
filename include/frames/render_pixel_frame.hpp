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
    RenderPixelFrame(const taeto::ColorFrame&);

    RenderPixelFrame(const taeto::RenderPixelFrame&);

    const taeto::CharFrame& chars() const;

    void chars(const taeto::CharFrame&);

    const taeto::ColorFrame& foreground_colors() const;

    void foreground_colors(const taeto::ColorFrame&);

    const taeto::ColorFrame& background_colors() const;

    void background_colors(const taeto::ColorFrame&);

    const taeto::BoolFrame& bolds() const;

    void bolds(const taeto::BoolFrame&);

    const taeto::BoolFrame& italics() const;

    void italics(const taeto::BoolFrame&);

    const taeto::BoolFrame& underlines() const;

    void underlines(const taeto::BoolFrame&);

    const taeto::BoolFrame& strikethroughs() const;

    void strikethroughs(const taeto::BoolFrame&);

    const taeto::VectorFrame& normals() const;

    void normals(const taeto::VectorFrame&);

    const taeto::UCharFrame& specularities() const;

    void specularities(const taeto::UCharFrame&);
};

}   // namespace taeto

#endif  // FRAMES_RENDER_PIXEL_FRAME_HPP_
