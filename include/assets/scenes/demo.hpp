#ifndef ASSETS_SCENES_DEMO_H_
#define ASSETS_SCENES_DEMO_H_

#include <chrono>
#include <memory>
#include <random>

#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

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

class VaporwaveSun : public Sprite
{
public:
    VaporwaveSun(glm::vec3 color1, glm::vec3 color2);

    ~VaporwaveSun() { };

    taeto::RenderPixel get_pixel_at(glm::uvec2) override;

private:
    taeto::RenderPixelFrame frame_;
};


class Demo : public Scene
{
public:
    Demo();

    ~Demo();

    void animate();

    void load();

private:
    std::shared_ptr<taeto::VaporwaveSun> sun_;
    std::shared_ptr<taeto::Stars> stars_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_DEMO_H_
