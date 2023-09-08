#ifndef ASSETS_SCENES_SPRITE_ORIENTATION_TEST_H_
#define ASSETS_SCENES_SPRITE_ORIENTATION_TEST_H_

#include <memory>

#include "engine.hpp"
#include "assets/lights/directional_light.hpp"
#include "assets/objects/checkerboard.hpp"

namespace taeto
{

class SpriteOrientationTest : public Scene
{
public:
    SpriteOrientationTest();

    ~SpriteOrientationTest();

    void animate();

    void load();

private:
    std::shared_ptr<taeto::Checkerboard> z_plane_checkerboard_;

    std::shared_ptr<taeto::Checkerboard> y_plane_checkerboard_;

    std::shared_ptr<taeto::DirectionalLight> dl_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_SPRITE_ORIENTATION_TEST_H_
