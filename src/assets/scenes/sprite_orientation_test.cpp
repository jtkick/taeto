#include "assets/scenes/sprite_orientation_test.hpp"

#include <memory>

#include "engine.hpp"

namespace taeto
{

SpriteOrientationTest::SpriteOrientationTest()
{
    z_plane_checkerboard_ = std::make_shared<taeto::Checkerboard>(
        20, 20, 'Z', taeto::Color(255, 0, 0));
    z_plane_checkerboard_->move(-10, -10, -10);

    y_plane_checkerboard_ = std::make_shared<taeto::Checkerboard>(
        20, 20, 'Y', taeto::Color(0, 255, 0));
    y_plane_checkerboard_->move(-30, -10, -10);

    taeto::Color c(255, 255, 255);
    taeto::Vector v(0, 0, 127);
    dl_ = std::make_shared<taeto::DirectionalLight>(c, v);
}

SpriteOrientationTest::~SpriteOrientationTest()
{

}

void SpriteOrientationTest::animate()
{

}

void SpriteOrientationTest::load()
{
    // Load all assets
    taeto::load_sprite(z_plane_checkerboard_);
    taeto::load_sprite(y_plane_checkerboard_);
    taeto::load_light(dl_);
}

}   // namespace taeto
