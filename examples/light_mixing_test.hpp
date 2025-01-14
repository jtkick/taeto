#ifndef ASSETS_SCENES_LIGHT_MIXING_TEST_H_
#define ASSETS_SCENES_LIGHT_MIXING_TEST_H_

#include <memory>

#include <glm/glm.hpp>

#include "assets/lights/spotlight.hpp"
#include "components/render_pixel.hpp"
#include "engine.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/sprite.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class WhiteBackdrop: public Sprite
{
public:
    WhiteBackdrop()
    {
        // this->position({-100, -50, 0});

        respect_light_sources_ = true;

        taeto::RenderPixel p(' ', {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, false);
        frame_ = taeto::RenderPixelFrame(glm::uvec2(200, 65), p);
    };

    taeto::RenderPixel get_pixel_at(glm::uvec2 v)
    {
        return frame_.at(v);
    }

    uint height()
    {
        return frame_.height();
    }

    uint width()
    {
        return frame_.width();
    }

    char plane_orientation()
    {
        return 'Z';
    }

private:
    taeto::RenderPixelFrame frame_;
};

class LightMixingTest : public Scene
{
public:
    LightMixingTest()
    {
        // Load backdrop
        backdrop = std::make_shared<taeto::WhiteBackdrop>();
        backdrop->move({-100, -32, -25});

        // Load spotlights
        red_light = std::make_shared<taeto::Spotlight>(glm::dvec3(1.0, 0.0, 0.0), 0.8, 30);
        red_light->move({0, -7, 0});

        green_light = std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 1.0, 0.0), 0.8, 30);
        green_light->move({-21, 5, 0});

        blue_light = std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 0.0, 1.0), 0.8, 30);
        blue_light->move({21, 5, 0});
    }

    ~LightMixingTest() {};

    void animate() {};

    void load()
    {
        taeto::load_sprite(backdrop);
        taeto::load_light(red_light);
        taeto::load_light(green_light);
        taeto::load_light(blue_light);
    }

private:
    std::shared_ptr<taeto::WhiteBackdrop> backdrop;
    std::shared_ptr<taeto::Spotlight> red_light;
    std::shared_ptr<taeto::Spotlight> green_light;
    std::shared_ptr<taeto::Spotlight> blue_light;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_LIGHT_MIXING_TEST_H_
