#include "taeto/shaders/shader.hpp"

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

namespace shaders
{

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::animate()
{

}

taeto::RenderPixel Shader::shade(
    taeto::RenderPixel prev_pixel,
    glm::uvec2 frame_shape,
    glm::uvec2 pos_in_frame,
    glm::dvec3 pos_in_world,
    glm::dvec3 camera_pos)
{

}

}   // namespace shaders

}   // namespace taeto
