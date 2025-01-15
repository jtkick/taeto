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

            // For calculating normals, correct y value to make it easier
            double y_loc = (i * 2.5) + 1.5;
            double x_loc = j + 0.5;

            double y_dist = y_loc - radius;
            double x_dist = x_loc - radius;

            // Get normal vector in relation to the radius
            double y_comp = y_dist / radius;
            double x_comp = x_dist / radius;
            double z_comp = std::cos(
                (std::sqrt(y_dist*y_dist + x_dist*x_dist) / radius) *
                1.57079632679);

            // If no z component, we've gone off the edge of the sphere, so
            // make all of these pixels fully transparent
            double distance = std::sqrt(y_dist*y_dist + x_dist*x_dist);
            if (distance >= radius)
                pixel.render = false;

            if (!spherical_normals)
                continue;

            // Calculate normal
            pixel.normal = glm::vec3(
                (x_loc/diameter) - 0.5,
                (y_loc/diameter) - 0.5,
                z_comp/2
            );
        }
    }
}

taeto::RenderPixel Circle::get_pixel_at(glm::uvec2 pos)
{
    return frame_.at(pos);
}

}   // namespace taeto
