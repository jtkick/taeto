#ifndef SHADERS_CHECKERBOARD_HPP_
#define SHADERS_CHECKERBOARD_HPP_

#include <glm/glm.hpp>

#include "taeto/shaders/shader.hpp"
#include "taeto/components/render_pixel.hpp"

namespace taeto
{

namespace shaders
{

class Checkerboard : public Shader
{
public:
    Checkerboard() { };

    ~Checkerboard() { };

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos);
};

}   // namespace shaders

}   // namespace taeto

#endif  // SHADERS_CHECKERBOARD_HPP_