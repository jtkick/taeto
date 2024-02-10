#ifndef FRAMES_DISPLAY_PIXEL_FRAME_HPP_
#define FRAMES_DISPLAY_PIXEL_FRAME_HPP_

#include "components/display_pixel.hpp"
#include "frames/char_frame.hpp"
#include "frames/frame.hpp"
#include "frames/uchar_frame.hpp"
#include "frames/vec3_frame.hpp"

namespace taeto
{

// Forward includes
class CharFrame;
class Vec3Frame;
class UCharFrame;
class DisplayPixelFrame : public taeto::Frame<taeto::DisplayPixel>
{
public:
    DisplayPixelFrame();

    DisplayPixelFrame(glm::uvec2 shape,
                      taeto::DisplayPixel d = taeto::DisplayPixel())
        : Frame(shape, d) { };

    ~DisplayPixelFrame() { };

    taeto::CharFrame chars();

    void chars(taeto::CharFrame&);

    taeto::Vec3Frame fg_colors();

    void fg_colors(taeto::Vec3Frame&);

    taeto::Vec3Frame bg_colors();

    void bg_colors(taeto::Vec3Frame&);

    taeto::UCharFrame bolds();

    void bolds(taeto::UCharFrame&);

    taeto::UCharFrame italics();

    void italics(taeto::UCharFrame&);

    taeto::UCharFrame underlines();

    void underlines(taeto::UCharFrame&);

    taeto::UCharFrame strikethroughs();

    void strikethroughs(taeto::UCharFrame&);

    void add_string(int, int, std::string);
};

}   // namespace taeto

#endif  // FRAMES_DISPLAY_PIXEL_FRAME_HPP_
