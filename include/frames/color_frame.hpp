#ifndef FRAMES_COLOR_FRAME_HPP_
#define FRAMES_COLOR_FRAME_HPP_

#include "components/color.hpp"
#include "frames/frame.hpp"
#include "frames/uchar_frame.hpp"

namespace taeto
{

// Forward includes
class UCharFrame;

class ColorFrame : Frame<taeto::Color>
{
public:
    ColorFrame();

    ColorFrame(std::string path);

    ~ColorFrame();

    const taeto::UCharFrame& reds() const;

    void reds(const taeto::UCharFrame&);

    const taeto::UCharFrame& greens() const;

    void greens(const taeto::UCharFrame&);

    const taeto::UCharFrame& blues() const;

    void blues(const taeto::UCharFrame&);

    const taeto::UCharFrame& alphas() const;

    void alphas(const taeto::UCharFrame&);

    taeto::UCharFrame from_black_and_white(std::string);
};

}   // namespace taeto

#endif  // FRAMES_COLOR_FRAME_HPP_
