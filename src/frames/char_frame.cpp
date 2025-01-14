#include "taeto/frames/char_frame.hpp"

#include <fstream>
#include <iostream>

#include <glm/glm.hpp>

namespace taeto
{

CharFrame::CharFrame()
{

}

CharFrame::CharFrame(glm::uvec2 shape, char c)
{
    resize(shape, c);
}

}   // namespace taeto
