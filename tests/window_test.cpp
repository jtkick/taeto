#ifndef ASSETS_SCENES_WINDOW_TEST_H_
#define ASSETS_SCENES_WINDOW_TEST_H_

#include <memory>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/engine.hpp"
#include "taeto/scenes/scene.hpp"
#include "taeto/shaders/checkerboard.hpp"
#include "taeto/widgets/horizontal_layout.hpp"
#include "taeto/widgets/widget.hpp"
#include "taeto/widgets/text_box.hpp"

class TestWindow : public taeto::Widget
{
public:
    TestWindow()
    {
        hl_.add_widget(std::make_shared<taeto::TextBox>("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."), 1);
        hl_.add_widget(std::make_shared<taeto::TextBox>("THIS IS A TEST"), 1);
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

    taeto::DisplayPixelFrame render()
    {
        taeto::DisplayPixelFrame result(size());
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

        taeto::DisplayPixelFrame l = hl_.render();
        result.apply(
            l,
            glm::uvec2(2, 1),
            false,
            [](taeto::DisplayPixel& a, taeto::DisplayPixel& b)->taeto::DisplayPixel&
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
    taeto::HorizontalLayout hl_;
};

class WindowTest : public taeto::Scene
{
public:
    WindowTest()
    {
        cb_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(1000, 1000),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        cb_->position({
            -((double)cb_->width()/2),
            -((double)cb_->height()/2),
            -10});
        cb_->add_shader(std::make_shared<taeto::shaders::Checkerboard>());
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
    std::shared_ptr<taeto::Rectangle> cb_;
    // std::shared_ptr<Widget> w_;
    // std::shared_ptr<TextBox> tb_;
    std::shared_ptr<TestWindow> tw_;
};

int main()
{
    taeto::set_debug_mode(true);
    taeto::load_scene(std::make_shared<WindowTest>());
    taeto::run();
}

#endif  // ASSETS_SCENES_WINDOW_TEST_H_
