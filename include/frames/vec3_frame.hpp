#ifndef FRAMES_VEC3_FRAME_HPP_
#define FRAMES_VEC3_FRAME_HPP_

#include "frames/frame.hpp"
#include "frames/float_frame.hpp"

#include <glm/glm.hpp>

namespace taeto
{

// Forward includes
class FloatFrame;
class Vec3Frame : public taeto::Frame<glm::vec3>
{
public:
    Vec3Frame();

    Vec3Frame(glm::uvec2 shape, glm::vec3 v = glm::vec3(0.0, 0.0, 0.0));

    Vec3Frame(std::string path);

    ~Vec3Frame() { };

    taeto::FloatFrame x();

    void x(taeto::FloatFrame&);

    taeto::FloatFrame y();

    void y(taeto::FloatFrame&);

    taeto::FloatFrame z();

    void z(taeto::FloatFrame&);
};

}   // namespace taeto

#endif  // FRAMES_VEC3_FRAME_HPP_
