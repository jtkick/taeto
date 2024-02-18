#ifndef ASSETS_SCENES_DEMO_H_
#define ASSETS_SCENES_DEMO_H_

#include <chrono>
#include <memory>
#include <random>

#include "assets/sprites/rectangle.hpp"
#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class TaetoLogo : public Sprite
{
public:
    TaetoLogo(glm::vec3 color);

    ~TaetoLogo() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

private:
    taeto::RenderPixelFrame frame_;
};

class GridShader : public Shader
{
public:
    GridShader(glm::vec3 c, float d);

    ~GridShader() { };

    void animate();

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos);

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
    Stars(float density);

    ~Stars() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

private:
    std::mt19937 rng_;

    taeto::RenderPixelFrame frame_;
};

class StarsGradient : public Shader
{
public:
    StarsGradient(glm::vec3 color);

    ~StarsGradient() { };

    taeto::RenderPixel shade(
        taeto::RenderPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame,
        glm::dvec3 pos_in_world,
        glm::dvec3 camera_pos);

private:
    glm::vec3 color_;
};

class VaporwaveSun : public Sprite
{
public:
    VaporwaveSun(glm::vec3 color1, glm::vec3 color2);

    ~VaporwaveSun() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

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
    Demo();

    ~Demo();

    void animate();

    void load();

private:
    std::shared_ptr<taeto::TaetoLogo> logo_;
    std::shared_ptr<taeto::Rectangle> grid_rect_;
    std::shared_ptr<taeto::VaporwaveSun> sun_;
    std::shared_ptr<taeto::Stars> stars_;
    std::shared_ptr<taeto::StarsGradient> stars_shader_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_DEMO_H_
