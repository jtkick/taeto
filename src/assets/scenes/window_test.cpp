#include "assets/scenes/window_test.hpp"

#include <memory>

#include "engine.hpp"
#include "assets/lights/point_light.hpp"
#include "assets/sprites/checkerboard.hpp"
#include "systems/window_system/widget.hpp"
#include "systems/window_system/text_box.hpp"

namespace taeto
{

WindowTest::WindowTest()
{
    cb_ = std::make_shared<taeto::Checkerboard>(glm::uvec2(1000, 1000), glm::vec3{1.0, 1.0, 1.0}, false);
    cb_->position({
        -((double)cb_->width()/2),
        -((double)cb_->height()/2),
        -10});

    // w_ = std::make_shared<Widget>("main");
    // w_->geometry(0, 0, 2, 20);
    // std::shared_ptr text = std::make_shared<TextBox>("text");
    // text->text("this is a test");


}

WindowTest::~WindowTest()
{

}

void WindowTest::load()
{
    taeto::load_sprite(cb_);
}

}   // namespace taeto
