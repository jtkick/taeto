#include "assets/object/sphere.hpp"

#include <memory>

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "components/render_pixel_frame.hpp"
#include "components/sprite.hpp"
#include "engine.hpp"

namespace taeto
{

Sphere::Sphere(int diameter)
{
    int height = (int)(diameter / 2.5);
    int width = diameter;

    double radius = (double)diameter / 2.0f;

    const double HALF_PI = 1.57079632679;

    current_frame = taeto::Frame(height, width);

    // Initialize pixels
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            taeto::Pixel& pixel = current_frame.at(i, j);
            pixel.char = ' ';
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
            if (distance > radius)
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

Sphere::load()
{
    taeto::load(light_);
}

Sphere::set_color(taeto::Color c_)
{
    current_frame.get_pixel(1, 1).foreground_color = c_;
}


void Sphere::handle_collision(std::shared_ptr<taeto::Sprite> other_sprite)
{

}

}   // namespace taeto
