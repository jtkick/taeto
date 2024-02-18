#include "shaders/shader.hpp"

#include "components/render_pixel.hpp"

namespace taeto
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

}   // namespace taeto
