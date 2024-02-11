#include "assets/scenes/demo.hpp"

#include <limits>
#include <random>
#include <stdlib.h>

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "engine.hpp"

namespace taeto
{

Stars::Stars(float density)
{
    // rng_ = std::mt19937(8675309);
    srand(8675309);

    shape_ = glm::uvec2(std::numeric_limits<unsigned int>::max());

}

taeto::RenderPixel Stars::get_pixel_at(glm::uvec2 pos)
{
    static taeto::RenderPixel pixel(
        ' ',
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.014, 0.0, 0.018, 1.0),
        false);

    srand(pos.y * height() * pos.x);
    if (rand() % 25 == 0)
        pixel.c = '.';
    else
        pixel.c = ' ';

    return pixel;
}


VaporwaveSun::VaporwaveSun(glm::vec3 color1, glm::vec3 color2)
{
    uint diameter = 45;
    uint height = (int)(diameter / 2.5);
    uint width = diameter;
    shape_ = glm::uvec2(width, height);

    double radius = (double)diameter / 2.0f;

    frame_ = taeto::RenderPixelFrame(glm::uvec2(width, height));

    // Get color difference to calculate gradient
    glm::vec3 color_steps = (color1 - color2) / (float)height;

    // Initialize pixels
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            taeto::RenderPixel& pixel = frame_.at(glm::uvec2(j, i));

            // Compute background color gradient
            pixel.bg_color = glm::vec4(
                color1.x - (color_steps.x * i),
                color1.y - (color_steps.y * i),
                color1.z - (color_steps.z * i),
                1.0);

            // If no z component, we've gone off the edge of the sphere, so
            // make all of these pixels fully transparent
            double y_loc = (i * 2.5) + 1.5;
            double x_loc = j + 0.5;
            double y_dist = y_loc - radius;
            double x_dist = x_loc - radius;
            double distance = std::sqrt(y_dist*y_dist + x_dist*x_dist);
            if (distance >= radius)
                pixel.render = false;
        }
    }

    // Cut slots into the sun like vaporwave images always do for some reason
    for (int i = height - 1; i >= height / 2; --i)
        if ((height - i) % 2 == 0)
            for (int j = 0; j < width; ++j)
                frame_.at(glm::uvec2(j, i)).render = false;
}

taeto::RenderPixel VaporwaveSun::get_pixel_at(glm::uvec2 pos)
{
    return frame_.at(pos);
}


Demo::Demo()
{
    sun_ = std::make_shared<taeto::VaporwaveSun>(glm::vec3(4.0, 1.75, 0.0), glm::vec3(3.0, 0.0, 1.3));
    sun_->position({-((double)sun_->width()/2), -15, -10});
    stars_ = std::make_shared<taeto::Stars>(0.0);
    stars_->position({
        -((double)stars_->width()/2),
        -((double)stars_->height()/2),
        -1000});
}

Demo::~Demo()
{

}

void Demo::load()
{
    taeto::load_sprite(stars_);
    taeto::load_sprite(sun_);
}

void Demo::animate()
{

}

}   // namespace taeto
