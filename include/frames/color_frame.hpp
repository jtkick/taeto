#ifndef FRAMES_COLOR_FRAME_HPP_
#define FRAMES_COLOR_FRAME_HPP_

#include "components/color.hpp"
#include "frames/frame.hpp"
#include "frames/uchar_frame.hpp"

namespace taeto
{

// Forward includes
class UCharFrame;

class ColorFrame : public Frame<taeto::Color>
{
public:
    ColorFrame();

    ColorFrame(
        unsigned long int,
        unsigned long int,
        taeto::Color c = taeto::Color());

    ColorFrame(std::string path);

    ~ColorFrame() { };

    taeto::UCharFrame reds();

    void reds(taeto::UCharFrame&);

    taeto::UCharFrame greens();

    void greens(taeto::UCharFrame&);

    taeto::UCharFrame blues();

    void blues(taeto::UCharFrame&);

    taeto::UCharFrame alphas();

    void alphas(taeto::UCharFrame&);

    taeto::UCharFrame from_black_and_white(std::string);
};

}   // namespace taeto

#endif  // FRAMES_COLOR_FRAME_HPP_
