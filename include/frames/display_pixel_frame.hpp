#ifndef FRAMES_DISPLAY_PIXEL_FRAME_HPP_
#define FRAMES_DISPLAY_PIXEL_FRAME_HPP_

#include "components/display_pixel.hpp"
#include "frames/bool_frame.hpp"
#include "frames/char_frame.hpp"
#include "frames/color_frame.hpp"
#include "frames/frame.hpp"

namespace taeto
{

// Forward includes
class BoolFrame;
class CharFrame;
class ColorFrame;

class DisplayPixelFrame : public Frame<taeto::DisplayPixel>
{
public:
    DisplayPixelFrame();

    DisplayPixelFrame(unsigned long int h, unsigned long int w, taeto::DisplayPixel d = taeto::DisplayPixel()): Frame(h, w, d) {};

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

    void add_string(int, int, std::string);
};

}   // namespace taeto

#endif  // FRAMES_DISPLAY_PIXEL_FRAME_HPP_
