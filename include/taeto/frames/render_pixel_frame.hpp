#ifndef FRAMES_RENDER_PIXEL_FRAME_HPP_
#define FRAMES_RENDER_PIXEL_FRAME_HPP_

#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/char_frame.hpp"
#include "taeto/frames/float_frame.hpp"
#include "taeto/frames/frame.hpp"
#include "taeto/frames/uchar_frame.hpp"
#include "taeto/frames/vec3_frame.hpp"
#include "taeto/frames/vec4_frame.hpp"

namespace taeto
{

// Forward includes
class CharFrame;
class FloatFrame;
class UCharFrame;
class Vec3Frame;
class Vec4Frame;
class RenderPixelFrame : public taeto::Frame<taeto::RenderPixel>
{
public:
    RenderPixelFrame();

    RenderPixelFrame(glm::uvec2 shape,
                     taeto::RenderPixel d = taeto::RenderPixel())
        : Frame(shape, d) { };

    RenderPixelFrame(const taeto::Vec4Frame&);

    RenderPixelFrame(const taeto::RenderPixelFrame&);

    ~RenderPixelFrame() { };

    taeto::CharFrame chars();

    void chars(taeto::CharFrame&);

    taeto::Vec4Frame fg_colors();

    void fg_colors(taeto::Vec4Frame&);

    taeto::Vec4Frame bg_colors();

    void bg_colors(taeto::Vec4Frame&);

    taeto::UCharFrame bolds();

    void bolds(taeto::UCharFrame&);

    taeto::UCharFrame italics();

    void italics(taeto::UCharFrame&);

    taeto::UCharFrame underlines();

    void underlines(taeto::UCharFrame&);

    taeto::UCharFrame strikethroughs();

    void strikethroughs(taeto::UCharFrame&);

    taeto::Vec3Frame normals();

    void normals(taeto::Vec3Frame&);

    taeto::FloatFrame specularities();

    void specularities(taeto::FloatFrame&);
};

}   // namespace taeto

#endif  // FRAMES_RENDER_PIXEL_FRAME_HPP_
