#include "assets/scenes/window_test.hpp"

#include <memory>
#include <vector>

#include "engine.hpp"
#include "assets/lights/point_light.hpp"
#include "assets/sprites/checkerboard.hpp"
#include "components/display_pixel.hpp"
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

    w_ = std::make_shared<Widget>("main");
    w_->pos({20, 5});
    w_->size({20, 2});

    DisplayPixelFrame t({14, 1});
    std::string tt = "this is a test";
    for (int i = 0; i < t.width(); i++)
    {
        t.at({i, 0}).c = tt.at(i);
        t.at({i, 0}).bg_color = {0, 0, 0, 0.5};
    }
    tb_ = std::make_shared<TextBox>();
    tb_->text(t);
    tb_->pos({10, 10});

}

WindowTest::~WindowTest()
{

}

void WindowTest::load()
{
    taeto::load_sprite(cb_);
    taeto::load_widget(tb_);
}

}   // namespace taeto
