#ifndef ASSETS_SCENES_HDR_TEST_H_
#define ASSETS_SCENES_HDR_TEST_H_

#include <chrono>
#include <memory>

#include "assets/lights/point_light.hpp"
#include "assets/lights/spotlight.hpp"
#include "assets/sprites/checkerboard.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class HDRTest : public Scene
{
public:
    HDRTest();

    ~HDRTest();

    void load();

private:
    std::shared_ptr<taeto::Checkerboard> checkerboard_;
    std::shared_ptr<taeto::PointLight> red_light_;
    std::shared_ptr<taeto::Spotlight> spotlight_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_HDR_TEST_H_
