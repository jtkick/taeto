#ifndef TESTS_COLLISION_DETECTION_TEST_HPP_
#define TESTS_COLLISION_DETECTION_TEST_HPP_

#include <memory>

#include "engine.hpp"
#include "assets/lights/directional_light.hpp"
#include "assets/objects/moving_box.hpp"
#include "scenes/scene.hpp"
#include "assets/objects/stationary_box.hpp"

namespace taeto
{

class CollisionDetectionTest : public Scene
{
public:
    CollisionDetectionTest();

    ~CollisionDetectionTest();

    void animate();

    void load();

private:
    std::shared_ptr<bool> space_pressed_;

    std::shared_ptr<taeto::StationaryBox> stat_box_;

    std::shared_ptr<taeto::MovingBox> mov_box_;

    std::shared_ptr<taeto::DirectionalLight> dl_;
};

}   // namespace taeto

#endif  // TESTS_COLLISION_DETECTION_TEST_HPP_
