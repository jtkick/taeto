#ifndef ASSETS_SCENES_LIGHT_MIXING_TEST_H_
#define ASSETS_SCENES_LIGHT_MIXING_TEST_H_

#include <memory>

#include "assets/lights/spotlight.hpp"
#include "assets/objects/white_backdrop.hpp"
#include "engine.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class LightMixingTest : public Scene
{
public:
    LightMixingTest();

    ~LightMixingTest();

    void animate();

    void load();

private:
    std::shared_ptr<taeto::WhiteBackdrop> backdrop;
    std::shared_ptr<taeto::Spotlight> red_light;
    std::shared_ptr<taeto::Spotlight> green_light;
    std::shared_ptr<taeto::Spotlight> blue_light;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_LIGHT_MIXING_TEST_H_
