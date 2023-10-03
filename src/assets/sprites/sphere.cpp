#include "assets/sprites/sphere.hpp"

#include <memory>

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"
#include "engine.hpp"

namespace taeto
{

Sphere::Sphere(int diameter)
{
    unsigned long int height = (int)(diameter / 2.5);
    unsigned long int width = diameter;

    double radius = (double)diameter / 2.0f;

    frame_ = taeto::RenderPixelFrame(height, width);

    // Initialize pixels
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            taeto::RenderPixel& pixel = frame_.at(i, j);
            pixel.c = ' ';
            pixel.foreground_color = taeto::Color(255, 255, 255);
            pixel.background_color = taeto::Color(255, 255, 255);

            // For calculating normals, correct y value to make it easier
            double y_loc = (i * 2.5) + 0.5;
            double x_loc = j + 0.5;

            // Get normal vector in relation to the radius
            double y_comp = (radius - y_loc) / radius;
            double x_comp = (radius - x_loc) / radius;
            double z_comp = std::sqrt(y_comp*y_comp + x_comp*x_comp);

            // If no z component, we've gone off the edge of the sphere, so
            // make all of these pixels fully transparent
            if (z_comp < 0.0)
                pixel.foreground_color = taeto::Color(255, 0, 255, 0);

            // Calculate normal
            taeto::Vector v = taeto::Vector(
                (x_comp * 255) - 128,
                (y_comp * 255) - 128,
                z_comp * 127
            );
            pixel.normal = v;
        }
    }
}

const taeto::RenderPixel& Sphere::get_pixel_at(
    uint64_t h, uint64_t w)
{
    return frame_.at(h, w);
}

uint64_t Sphere::height()
{
    return frame_.height();
}

uint64_t Sphere::width()
{
    return frame_.width();
}

bool Sphere::respect_light_sources()
{
    return true;
}

}   // namespace taeto
