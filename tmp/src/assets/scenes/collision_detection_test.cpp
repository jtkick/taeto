#include "assets/scenes/collision_detection_test.hpp"

#include <memory>

#include "engine.hpp"

namespace taeto
{

CollisionDetectionTest::CollisionDetectionTest()
{
    stat_box_ = std::make_shared<taeto::StationaryBox>();
    stat_box_->move(-40, -stat_box_->get_height()/2, -10);

    mov_box_ = std::make_shared<taeto::MovingBox>();
    mov_box_->move(40, -mov_box_->get_height()/2, -10);

    taeto::Color c(255, 255, 255);
    taeto::Vector v(0, 0, 127);
    dl_ = std::make_shared<taeto::DirectionalLight>(c, v);
}

CollisionDetectionTest::~CollisionDetectionTest()
{

}

void CollisionDetectionTest::animate()
{
    mov_box_->set_color(taeto::Color(0, 255, 0));

    // Move moving box based on space bar state
    if (*(space_pressed_))
    {
        // Move right
        mov_box_->move(1, 0, 0);
    }
    else
    {
        // Move left
        mov_box_->move(-1, 0, 0);
    }
}

void CollisionDetectionTest::load()
{
    // Load all assets
    taeto::load_sprite(stat_box_);
    taeto::load_sprite(mov_box_);
    taeto::load_light(dl_);

    space_pressed_ = taeto::get_button_reference(6);
}

}   // namespace taeto
