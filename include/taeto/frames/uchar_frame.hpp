#ifndef FRAMES_UCHAR_FRAME_HPP_
#define FRAMES_UCHAR_FRAME_HPP_

#include <glm/glm.hpp>

#include "taeto/frames/frame.hpp"

namespace taeto
{

class UCharFrame : public taeto::Frame<unsigned char>
{
public:
    UCharFrame();

    UCharFrame(glm::uvec2 shape, unsigned char c = 0);

    UCharFrame(std::string path);

    ~UCharFrame() { };
};

}   // namespace taeto

#endif  // FRAMES_UCHAR_FRAME_HPP_
