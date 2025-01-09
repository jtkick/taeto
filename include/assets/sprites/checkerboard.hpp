#ifndef ASSETS_OBJECTS_CHECKERBOARD_HPP_
#define ASSETS_OBJECTS_CHECKERBOARD_HPP_

#include <glm/glm.hpp>

#include "object/sprite.hpp"

namespace taeto
{

class Checkerboard: public taeto::Sprite
{
public:
    Checkerboard(glm::uvec2 s) :
        Checkerboard(s, {1.0, 1.0, 1.0})
        { }

    Checkerboard(glm::uvec2 s, glm::vec3 c, bool respect_light_sources = true);

    taeto::RenderPixel get_pixel_at(glm::uvec2 pos);

private:
    glm::vec4 light_color_;
    glm::vec4 dark_color_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_CHECKERBOARD_H_
