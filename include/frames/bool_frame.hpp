#ifndef FRAMES_BOOL_FRAME_H_
#define FRAMES_BOOL_FRAME_H_

#include "frames/frame.hpp"

namespace taeto
{

class BoolFrame : Frame<bool>
{
public:
    BoolFrame();

    BoolFrame(std::string path);

    ~BoolFrame();
};

}   // namespace taeto

#endif  // FRAMES_BOOL_FRAME_H_
