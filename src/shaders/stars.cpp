#include "taeto/shaders/stars.hpp"

#include <random>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

namespace shaders
{

taeto::RenderPixel Stars::shade(
    taeto::RenderPixel prev_pixel,
    glm::uvec2 frame_shape,
    glm::uvec2 pos_in_frame,
    glm::dvec3 pos_in_world,
    glm::dvec3 camera_pos)
{
    taeto::RenderPixel pixel(
        ' ', {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, true);
    srand(
        (pos_in_frame.y + offset_.y) *
        frame_shape.y *
        (pos_in_frame.x + offset_.x)
    );
    if (rand() % 15 == 0)
        pixel.c = '.';
    else
        pixel.c = ' ';

    return pixel;
}

}   // namespace shaders

}   // namespace taeto