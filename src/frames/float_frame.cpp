#include "frames/float_frame.hpp"

#include <glm/glm.hpp>

namespace taeto
{

FloatFrame::FloatFrame()
{

}

FloatFrame::FloatFrame(glm::uvec2 shape, float f)
{
    resize(shape, f);
}

}   // namespace taeto
