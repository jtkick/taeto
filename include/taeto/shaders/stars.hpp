#ifndef SHADERS_STARS_HPP_
#define SHADERS_STARS_HPP_

#include <glm/glm.hpp>

#include "taeto/shaders/shader.hpp"
#include "taeto/components/render_pixel.hpp"

namespace taeto
{

namespace shaders
{

class Stars : public Shader
{
public:
    Stars() : offset_({0, 0}) { };

    ~Stars() { };

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos);

    void offset(glm::ivec2 offset) { offset_ = offset; };
    
private:
    glm::ivec2 offset_;
};

}   // namespace shaders

}   // namespace taeto

#endif  // SHADERS_STARS_HPP_