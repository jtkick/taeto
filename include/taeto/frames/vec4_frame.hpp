#ifndef FRAMES_VEC4_FRAME_HPP_
#define FRAMES_VEC4_FRAME_HPP_

#include "taeto/frames/frame.hpp"
#include "taeto/frames/float_frame.hpp"

namespace taeto
{

// Forward includes
class FloatFrame;

class Vec4Frame : public taeto::Frame<glm::vec4>
{
public:
    Vec4Frame();

    Vec4Frame(glm::uvec2 shape, glm::vec4 v = glm::vec4());

    Vec4Frame(std::string path);

    ~Vec4Frame() { };

    taeto::FloatFrame x();

    void x(taeto::FloatFrame&);

    taeto::FloatFrame y();

    void y(taeto::FloatFrame&);

    taeto::FloatFrame z();

    void z(taeto::FloatFrame&);

    taeto::FloatFrame w();

    void w(taeto::FloatFrame&);

    taeto::FloatFrame from_black_and_white(std::string);
};

}   // namespace taeto

#endif  // FRAMES_VEC4_FRAME_HPP_
