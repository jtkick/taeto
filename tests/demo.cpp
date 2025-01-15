#ifndef TESTS_DEMO_HPP_
#define TESTS_DEMO_HPP_

#include <chrono>
#include <memory>
#include <random>

#include "taeto/engine.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/render_pixel_frame.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/scenes/scene.hpp"

namespace taeto
{

class TaetoLogo : public Sprite
{
public:
    TaetoLogo(glm::vec3 color)
    {
        std::vector<std::string> text_frame = {
            R"(      ############# #####       ########## ############  #########      )",
            R"(     ############# ######      ########## ############ ############     )",
            R"(         ####     #######     ####           ####     ####    ####      )",
            R"(        ####     ###  ###    #######        ####     ####    ####       )",
            R"(       ####     #########   #######        ####     ####    ####        )",
            R"(      ####     ##########  ####           ####     ####    ####         )",
            R"(     ####     ####   #### ##########     ####     ############          )",
            R"(    ####     ####    ##############     ####      ##########            )",
            R"(                                                                        )"
        };

        std::vector<glm::vec4> colors = {
            glm::vec4(0.1, 0.1, 1.0, 1.0),
            glm::vec4(0.2, 0.2, 1.0, 1.0),
            glm::vec4(0.3, 0.3, 1.0, 1.0),
            glm::vec4(0.5, 0.5, 1.0, 1.0),
            glm::vec4(0.5, 0.5, 1.0, 1.0),
            glm::vec4(0.5, 0.5, 1.0, 1.0),
            glm::vec4(0.2, 0.2, 1.0, 1.0),
            glm::vec4(0.1, 0.1, 1.0, 1.0)
        };

        // Compile actual pixels
        shape_ = glm::uvec2(glm::uvec2(text_frame.at(0).size(), text_frame.size()));
        frame_ = taeto::RenderPixelFrame(shape_);
        for (int y = 0; y < shape_.y; ++y)
        {
            for (int x = 0; x < shape_.x; ++x)
            {
                taeto::RenderPixel& pixel = frame_.at(glm::uvec2(x, y));
                if (text_frame.at(y).at(x) != ' ')
                {
                    pixel.c = ' ';
                    pixel.fg_color = glm::vec4(color, 0.0);
                    pixel.bg_color = colors.at(y) * 5.0f;
                    pixel.bg_color.a = 1.0f;
                }
                else
                {
                    if (x-1 >= 0 && y-1 >= 0 && text_frame.at(y-1).at(x-1) == '#')
                        pixel.bg_color = glm::vec4(0.08, 0.08, 0.8, 1.0);
                    else
                        pixel.render = false;
                }
            }
        }
    };

    ~TaetoLogo() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2 pos) override
    {
        return frame_.at(pos);
    };

private:
    taeto::RenderPixelFrame frame_;
};

class GridShader : public taeto::shaders::Shader
{
public:
    GridShader(glm::vec3 c, float d)
        : color_(c), density_(d), offset_(0), last_animate_(ms_since_epoch()),
          stopwatch_(std::chrono::milliseconds(0)) { };

    ~GridShader() { };

    void animate()
    {
        std::chrono::milliseconds frame_rate(40);

        stopwatch_ += ms_since_epoch() - last_animate_;
        last_animate_ = ms_since_epoch();

        while (stopwatch_ > std::chrono::milliseconds(frame_rate))
        {
            stopwatch_ -= std::chrono::milliseconds(frame_rate);
            offset_ = offset_ + 0.1;
            if (offset_ >= 1.0) offset_ = 0.0;
        }
    };

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos)
    {
        // return prev_pixel;

        // Try different method
        glm::uvec2 half_frame_size =
            glm::uvec2(frame_shape.x / 2, frame_shape.y / 2);
        glm::uvec2 dist_from_center = pos_in_frame - half_frame_size;
        glm::vec2 dist_from_center_ratio = glm::vec2(
            (float)dist_from_center.x / (float)half_frame_size.x,
            (float)dist_from_center.y / (float)half_frame_size.y);

        int slope = dist_from_center.y * density_;

        // Foregound is always the same solid color, if shown at all
        prev_pixel.fg_color = glm::vec4(color_, 1.0);

        // The background color should fade in as we get closer to the horizon,
        // and eventually completely overtake the foreground
        prev_pixel.bg_color = glm::vec4(
            (color_ * 0.02f) +
            (color_ * (float)std::pow(1.0 - dist_from_center_ratio.y, 12)), 1.0);

        // Draw vertical lines
        if (slope == 0)
            return prev_pixel;
        if (std::abs((int)dist_from_center.x) % slope <= std::abs((int)(dist_from_center.x) / slope / 2))
            prev_pixel.c = '*';

        // Draw horizontal lines
        // Evertime it crosses an integer value, we show the character
        if ((int)(std::pow(dist_from_center.y, 9.0f/20.0f) - offset_) !=
            (int)(std::pow(dist_from_center.y-1, 9.0f/20.0f) - offset_))
            prev_pixel.c = '*';

        return prev_pixel;
    };

private:
    glm::vec3 color_;
    float density_;

    std::chrono::milliseconds last_animate_;
    std::chrono::milliseconds stopwatch_;
    float offset_;
};

class Stars : public Sprite
{
public:
    Stars(float density)
    {
        shape_ = glm::uvec2(std::numeric_limits<unsigned int>::max());
    };

    ~Stars() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2 pos) override
    {
        static taeto::RenderPixel pixel(
            ' ',
            glm::vec4(1.0, 0.66, 0.82, 1.0),
            glm::vec4(0.014, 0.0, 0.018, 1.0),
            false
        );

        srand(pos.y * height() * pos.x);
        if (rand() % 25 == 0)
            pixel.c = '.';
        else
            pixel.c = ' ';

        return pixel;
    };

private:
    std::mt19937 rng_;

    taeto::RenderPixelFrame frame_;
};

class StarsGradient : public taeto::shaders::Shader
{
public:
    StarsGradient(glm::vec3 color) : color_(color) { };

    ~StarsGradient() { };

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos)
    {
        // Get distance from vertical center of screen
        float half_frame_height = (float)frame_shape.y / 2;
        float dist_from_center =
            std::abs(((float)pos_in_frame.y - half_frame_height) /
                    half_frame_height);

        // Compute gradient
        // Fade in blue faster than red to get a nice black to purple to pink
        // 3-shade gradient
        // Add a little extra as well to make them brighter and bloom a little
        float glow = 5.0;
        prev_pixel.bg_color += glm::vec4(
            color_.x * std::pow(1.0 - dist_from_center, 8) * glow,
            color_.y * std::pow(1.0 - dist_from_center, 3) * glow,
            color_.z * std::pow(1.0 - dist_from_center, 3) * glow,
            1.0);
        return prev_pixel;
    };

private:
    glm::vec3 color_;
};

class VaporwaveSun : public Sprite
{
public:
    VaporwaveSun(glm::vec3 color1, glm::vec3 color2)
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
                    1.0) * 2.0f;
                pixel.bg_color.a = 1.0f;

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
    };

    ~VaporwaveSun() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2 pos) override
    {
        return frame_.at(pos);
    };

private:
    taeto::RenderPixelFrame frame_;
};

// class Mountains : public Sprite
// {
// public:
//     Mountains(glm::vec3 color);
//
//     ~Mountains() { };
//
//     taeto::RenderPixel get_pixel_at(glm::uvec2) override;
//
// private:
//     taeto::RenderPixelFrame frame_;
// };


class Demo : public Scene
{
public:
    Demo()
    {
        // Create Taeto logo
        logo_ = std::make_shared<taeto::TaetoLogo>(glm::vec3(3.0, 1.0, 2.0));
        logo_->position({-((double)logo_->width()/2),
                        -((double)logo_->height()/2),
                        -20});

        // Create grid rectangle
        unsigned int max = std::numeric_limits<unsigned int>::max();
        grid_rect_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(max, max/2),
            taeto::RenderPixel(' ', glm::vec4(0.0),
                            glm::vec4(0.0, 0.0, 0.0, 1.0), false));
        grid_rect_->position(glm::dvec3(
            -((double)grid_rect_->width()/2),
            0.0,
            -1000.0));
        auto grid_shader_ = std::make_shared<taeto::GridShader>(glm::vec3(0.0, 0.4, 2.0), 2.0);
        grid_rect_->add_shader(grid_shader_);

        // Create sun
        sun_ = std::make_shared<taeto::VaporwaveSun>(glm::vec3(4.0, 1.75, 0.0),
                                                    glm::vec3(3.0, 0.0, 1.3));
        sun_->position({-((double)sun_->width()/2), -18, -20.001});

        // Create stars backdrop
        stars_ = std::make_shared<taeto::Stars>(0.0);
        stars_->position({
            -((double)stars_->width()/2),
            -((double)stars_->height()/2),
            -1001});
        stars_shader_ = std::make_shared<taeto::StarsGradient>(glm::vec3(1.0, 0.1, 1.0));
        stars_->add_shader(stars_shader_);

        taeto::Camera& camera = taeto::get_camera();
        camera.position().z = -10;
    };

    ~Demo() { };

    void animate() { };

    void load()
    {
        taeto::load_sprite(logo_);
        taeto::load_sprite(grid_rect_);
        taeto::load_sprite(stars_);
        taeto::load_sprite(sun_);
    };

private:
    std::shared_ptr<taeto::TaetoLogo> logo_;
    std::shared_ptr<taeto::Rectangle> grid_rect_;
    std::shared_ptr<taeto::VaporwaveSun> sun_;
    std::shared_ptr<taeto::Stars> stars_;
    std::shared_ptr<taeto::StarsGradient> stars_shader_;
};

}   // namespace taeto

int main()
{
    std::shared_ptr<taeto::Demo> demo = std::make_shared<taeto::Demo>();
    taeto::load_scene(demo);
    taeto::run();
}

#endif  // TESTS_DEMO_HPP_
