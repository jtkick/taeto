#ifndef FRAMES_COLOR_FRAME_HPP_
#define FRAMES_COLOR_FRAME_HPP_

#include "components/color.hpp"
#include "frames/frame.hpp"
#include "frames/char_frame.hpp"

namespace taeto
{

// Forward includes
class CharFrame;

class ColorFrame : Frame<taeto::Vector>
{
public:
    ColorFrame();

    ColorFrame(std::string path);

    ~ColorFrame();

    const taeto::CharFrame& x() const;

    void x(const taeto::CharFrame&);

    const taeto::CharFrame& y() const;

    void y(const taeto::CharFrame&);

    const taeto::CharFrame& z() const;

    void z(const taeto::CharFrame&);
};

}   // namespace taeto

#endif  // FRAMES_COLOR_FRAME_HPP_
