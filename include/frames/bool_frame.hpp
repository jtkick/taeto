#ifndef FRAMES_BOOL_FRAME_HPP_
#define FRAMES_BOOL_FRAME_HPP_

#include "frames/frame.hpp"

namespace taeto
{

class BoolFrame : public Frame<bool>
{
public:
    BoolFrame();

    BoolFrame(std::string path);

    ~BoolFrame();
};

}   // namespace taeto

#endif  // FRAMES_BOOL_FRAME_HPP_
