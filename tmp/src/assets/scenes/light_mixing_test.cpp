#include "assets/scenes/light_mixing_test.hpp"

#include <memory>

#include "assets/lights/spotlight.hpp"
#include "assets/objects/white_backdrop.hpp"
#include "engine.hpp"

namespace taeto
{

LightMixingTest::LightMixingTest()
{
    // Load backdrop
    backdrop = std::make_shared<taeto::WhiteBackdrop>();
    backdrop->move(-100, -32, -25);

    // Load spotlights
    red_light = std::make_shared<taeto::Spotlight>(taeto::Color(255, 0, 0), 0.8, 30);
    red_light->move(0, -7, 0);

    green_light = std::make_shared<taeto::Spotlight>(taeto::Color(0, 255, 0), 0.8, 30);
    green_light->move(-21, 5, 0);

    blue_light = std::make_shared<taeto::Spotlight>(Color(0, 0, 255), 0.8, 30);
    blue_light->move(21, 5, 0);
}

LightMixingTest::~LightMixingTest()
{

}

void LightMixingTest::animate()
{

}

void LightMixingTest::load()
{
    taeto::load_sprite(backdrop);
    taeto::load_light(red_light);
    taeto::load_light(green_light);
    taeto::load_light(blue_light);
}

}   // namespace taeto
