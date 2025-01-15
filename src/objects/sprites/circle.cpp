#include "taeto/objects/sprites/circle.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/engine.hpp"

namespace taeto
{

Circle::Circle(int diameter, taeto::RenderPixel r, bool spherical_normals)
{
    uint height = (int)(diameter / 2.5);
    uint width = diameter;
    shape_ = {width, height};

    double radius = (double)diameter / 2.0f;

    frame_ = taeto::RenderPixelFrame(glm::uvec2(width, height));

    // Initialize pixels
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            taeto::RenderPixel& pixel = frame_.at(glm::uvec2(j, i));
            pixel = r;

            float x_radius = (float)width / 2;
            float y_radius = (float)height / 2;

            float x_norm = (static_cast<float>(j) + 0.5 - x_radius) / x_radius;
            float y_norm = (static_cast<float>(i) + 0.5 - y_radius) / y_radius;
            float xy_squared = x_norm * x_norm + y_norm * y_norm;

            if (xy_squared > 1.0f)
                pixel.render = false;

            if (!spherical_normals)
                continue;

            float z_norm = std::sqrt(1.0f - xy_squared);
            pixel.normal = glm::normalize(glm::vec3(x_norm, y_norm, z_norm));
        }
    }
}

taeto::RenderPixel Circle::get_pixel_at(glm::uvec2 pos)
{
    return frame_.at(pos);
}

}   // namespace taeto
