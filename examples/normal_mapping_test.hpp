#ifndef ASSETS_SCENES_NORMAL_MAPPING_TEST_H_
#define ASSETS_SCENES_NORMAL_MAPPING_TEST_H_

#include <chrono>
#include <memory>

#include "assets/lights/point_light.hpp"
#include "assets/sprites/sphere.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class NormalMappingTest : public Scene
{
public:
    NormalMappingTest();

    ~NormalMappingTest();

    void animate();

    void load();

private:
    int distance_ = 50;

    float speed_ = 5.0;

    float current_degree_ = 0.0;

    std::chrono::milliseconds last_animate_;
    std::chrono::milliseconds stopwatch_;

    // Assets
    std::shared_ptr<taeto::Sphere> s_;
    std::shared_ptr<taeto::PointLight> pl_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_NORMAL_MAPPING_TEST_H_
