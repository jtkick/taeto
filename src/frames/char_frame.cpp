 #include "frames/char_frame.hpp"

#include <fstream>
#include <iostream>

namespace taeto
{

CharFrame::CharFrame()
{

}

CharFrame::CharFrame(unsigned long int h, unsigned long int w)
{
    resize(h, w, ' ');
}

}   // namespace taeto
