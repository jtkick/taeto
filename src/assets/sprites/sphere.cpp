#include "assets/sprites/sphere.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"
#include "engine.hpp"

namespace taeto
{

Sphere::Sphere(int diameter)
{
    uint height = (int)(diameter / 2.5);
    uint width = diameter;

    double radius = (double)diameter / 2.0f;

    frame_ = taeto::RenderPixelFrame(glm::uvec2(width, height));

    // Initialize pixels
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            taeto::RenderPixel& pixel = frame_.at(glm::uvec2(j, i));
            pixel.c = ' ';
            pixel.fg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
            pixel.bg_color = glm::vec4(1.0, 1.0, 1.0, 1.0);

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

            // Calculate normal
            pixel.normal = glm::vec3(
                (x_loc/diameter) - 0.5,
                (y_loc/diameter) - 0.5,
                z_comp/2
            );
        }
    }
}

const taeto::RenderPixel& Sphere::get_pixel_at(glm::uvec2 pos)
{
    return frame_.at(pos);
}

uint Sphere::height()
{
    return frame_.height();
}

uint Sphere::width()
{
    return frame_.width();
}

bool Sphere::respect_light_sources()
{
    return true;
}

}   // namespace taeto
