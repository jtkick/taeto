#ifndef ASSETS_SCENES_WINDOW_TEST_H_
#define ASSETS_SCENES_WINDOW_TEST_H_

#include <memory>

#include "assets/sprites/checkerboard.hpp"
#include "engine.hpp"
#include "scenes/scene.hpp"
#include "systems/window_system/horizontal_layout.hpp"
#include "systems/window_system/widget.hpp"
#include "systems/window_system/text_box.hpp"

namespace taeto
{

class TestWindow : public Widget
{
public:
    TestWindow()
    {
        hl_.add_widget(std::make_shared<TextBox>("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."), 1);
        hl_.add_widget(std::make_shared<TextBox>("THIS IS A TEST"), 1);
    };

    ~TestWindow() {};

    void size(glm::uvec2 v)
    {
        size_ = v;
        hl_.size(v - glm::uvec2(4, 2));
    };

    glm::uvec2 size()
    {
        return size_;
    }

    DisplayPixelFrame render()
    {
        DisplayPixelFrame result(size());
        for (int y = 0; y < result.height(); y++)
        {
            for (int x = 0; x < result.width(); x++)
            {
                result.at({x, y}).bg_color = glm::vec4(0.0, 0.0, 0.0, 0.5);

                if (y == 0 || y == result.height()-1)
                    result.at({x, y}).c = '#';
                else if (x < 2 || x > result.width()-3)
                    result.at({x, y}).c = '#';

            }
        }

        DisplayPixelFrame l = hl_.render();
        result.apply(
            l,
            glm::uvec2(2, 1),
            false,
            [](DisplayPixel& a, DisplayPixel& b)->DisplayPixel&
            {
                a.c = b.c;
                a.fg_color = taeto::mix_colors(a.fg_color, b.fg_color);
                a.bg_color = taeto::mix_colors(a.bg_color, b.bg_color);
                a.bold = b.bold;
                a.italic = b.italic;
                a.underline = b.underline;
                a.strikethrough = b.strikethrough;
                return a;
            }
        );
        return result;
        
    };

protected:
    HorizontalLayout hl_;
};

class WindowTest : public taeto::Scene
{
public:
    WindowTest()
    {
        cb_ = std::make_shared<taeto::Checkerboard>(glm::uvec2(1000, 1000), glm::vec3{1.0, 1.0, 1.0}, false);
        cb_->position({
            -((double)cb_->width()/2),
            -((double)cb_->height()/2),
            -10});

        // w_ = std::make_shared<Widget>("main");
        // w_->position({20, 5});
        // w_->size({20, 2});

        // DisplayPixelFrame t({14, 1});
        // std::string tt = "this is a test";
        // for (int i = 0; i < t.width(); i++)
        // {
        //     t.at({i, 0}).c = tt.at(i);
        //     t.at({i, 0}).bg_color = {0, 0, 0, 0.5};
        // }
        // tb_ = std::make_shared<TextBox>();
        // tb_->text(t);
        // tb_->position({-2, 10});
        tw_ = std::make_shared<TestWindow>();
        tw_->size({50, 10});
        tw_->position({40, 15});
    }

    ~WindowTest() {};

    void load()
    {
        taeto::load_sprite(cb_);
        // taeto::load_widget(tb_);
        taeto::load_widget(tw_);
    }

private:
    std::shared_ptr<Checkerboard> cb_;
    // std::shared_ptr<Widget> w_;
    // std::shared_ptr<TextBox> tb_;
    std::shared_ptr<TestWindow> tw_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_WINDOW_TEST_H_
