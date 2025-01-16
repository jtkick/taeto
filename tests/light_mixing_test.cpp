#include <memory>

#include <glm/glm.hpp>

#include "taeto/objects/lights/spotlight.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/engine.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/scenes/scene.hpp"

class LightMixingTest : public taeto::Scene
{
public:
    LightMixingTest()
    {
        // Load backdrop
        backdrop = std::make_shared<taeto::Rectangle>(
            glm::uvec2(200, 64),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        backdrop->position({-100, -32, -25});
        backdrop->respect_light_sources(true);
        
        // Load spotlights
        red_light = std::make_shared<taeto::Spotlight>(glm::dvec3(1.0, 0.0, 0.0), 0.8, 30);
        red_light->position({0, -7, 0});
        green_light = std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 1.0, 0.0), 0.8, 30);
        green_light->position({-21, 5, 0});
        blue_light = std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 0.0, 1.0), 0.8, 30);
        blue_light->position({21, 5, 0});
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
    std::shared_ptr<taeto::Rectangle> backdrop;
    std::shared_ptr<taeto::Spotlight> red_light;
    std::shared_ptr<taeto::Spotlight> green_light;
    std::shared_ptr<taeto::Spotlight> blue_light;
};

int main()
{
    taeto::set_debug_mode(true);
    taeto::load_scene(std::make_shared<LightMixingTest>());
    taeto::run();
}