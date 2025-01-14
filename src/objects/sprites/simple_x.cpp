#include "taeto/objects/sprites/simple_x.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

SimpleX::SimpleX()
{
    pixel_ = taeto::RenderPixel(
        'X',
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        false
    );
}

taeto::RenderPixel SimpleX::get_pixel_at(glm::uvec2 pos)
{
    return pixel_;
}

uint SimpleX::height()
{
    return 10;
}

uint SimpleX::width()
{
    return 20;
}

bool SimpleX::respect_light_sources()
{
    return false;
}

}   // namespace taeto
