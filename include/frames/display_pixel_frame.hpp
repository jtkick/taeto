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
};

}   // namespace taeto

#endif  // FRAMES_DISPLAY_PIXEL_FRAME_HPP_
