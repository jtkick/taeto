#ifndef FRAMES_BOOL_FRAME_HPP_
#define FRAMES_BOOL_FRAME_HPP_

#include "frames/frame.hpp"

namespace taeto
{

class BoolFrame : public Frame<bool>
{
public:
    BoolFrame();

    BoolFrame(unsigned long int h, unsigned long int w, bool b = false);

    BoolFrame(std::string path);

    ~BoolFrame();

    inline bool at(int y, int x) { return values_.at(y).at(x); };

    inline void set(int y, int x, bool val) { values_.at(y).at(x) = val; };
};

}   // namespace taeto

#endif  // FRAMES_BOOL_FRAME_HPP_
