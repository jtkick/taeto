#ifndef FRAMES_CHAR_FRAME_H_
#define FRAMES_CHAR_FRAME_H_

#include <algorithm>
#include <array>
#include <vector>

#include "lodepng.h"

#include "frames/frame.hpp"

namespace taeto
{

class UCharFrame : Frame<uint8_t>
{
public:
    UCharFrame();

    UCharFrame(unsigned long int, unsigned long int);

    UCharFrame(const UCharFrame&);

    UCharFrame(std::string);

    // Conversion constructors
    UCharFrame(const taeto::ColorFrame& cf);

    UCharFrame(const DisplayFrame&);

    UCharFrame(const RenderFrame&);

    ~UCharFrame();
};

}   // namespace taeto

#endif  // FRAMES_CHAR_FRAME_H_
