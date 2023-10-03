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

    const double HALF_PI = 1.57079632679;

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
            double y_loc = i * 2.5;
            double x_loc = j;

            // Get distance to center of circle
            double y_dist = radius - y_loc;
            double x_dist = radius - x_loc;
            double distance = std::sqrt(y_dist*y_dist + x_dist*x_dist);

            // If distance is greater than the radius, make the pixel invisible
            if (distance > radius + 0.2)
                pixel.foreground_color = taeto::Color(255, 0, 255, 0);

            // Get distance from center in radians
            double z_comp = (distance / radius) * HALF_PI;
            double y_comp = (y_dist / radius) * HALF_PI;
            double x_comp = (x_dist / radius) * HALF_PI;

            // Calculate normal
            taeto::Vector v = taeto::Vector(
                std::cos(x_comp) * 255,
                std::cos(y_comp) * 255,
                (std::cos(z_comp) * 127) + 127
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
