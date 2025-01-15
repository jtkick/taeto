#include "taeto/shaders/checkerboard.hpp"

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

namespace shaders
{

taeto::RenderPixel Checkerboard::shade(
    taeto::RenderPixel prev_pixel,
    glm::uvec2 frame_shape,
    glm::uvec2 pos_in_frame,
    glm::dvec3 pos_in_world,
    glm::dvec3 camera_pos)
{
    // Set background color to alternate in checkerboard pattern
    prev_pixel.bg_color = (pos_in_frame.x % 8 < 4)!=(pos_in_frame.y % 4 < 2)
        ? prev_pixel.bg_color : prev_pixel.bg_color * glm::vec4(0.5, 0.5, 0.5, 1.0);
    return prev_pixel;
}

}   // namespace shaders

}   // namespace taeto