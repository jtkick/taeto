#ifndef ASSETS_SCENES_WINDOW_TEST_H_
#define ASSETS_SCENES_WINDOW_TEST_H_

#include <memory>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/irenderable.hpp"
#include "taeto/objects/iwidget.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/engine.hpp"
#include "taeto/scenes/scene.hpp"
#include "taeto/shaders/checkerboard.hpp"
#include "taeto/tools.hpp"

class TextBox : public taeto::IWidget
{
public:
    TextBox(std::string text = "Hello world!") : text_(text) { };

    ~TextBox() { };

    taeto::RenderPixel pixel_at(const glm::uvec2& pos)
    {
        if ((pos.y * shape().x) + pos.x < text_.length())
            return taeto::RenderPixel(text_.at((pos.y * shape().x) + pos.x), glm::vec4(1,1,1,1), glm::vec4(0,0,0,0), false);
        return taeto::RenderPixel(' ', glm::vec4(0,0,0,0), glm::vec4(0,0,0,0), false);
    };

private:
    std::string text_;
};

class TestWindow : public taeto::IWidget
{
public:
    TestWindow()
    {
    
    };

    ~TestWindow() {};

    void shape(const glm::uvec2& s)
    {
        shape_ = s;
        child()->shape(s-glm::uvec2({4, 2}));
    };

    glm::uvec2& shape()
    {
        return shape_;
    };

    taeto::RenderPixel pixel_at(const glm::uvec2& pos)
    {
        taeto::RenderPixel ret = default_;
        if (pos.x == 0 || pos.x == shape().x-1)
        {
            if (pos.y == 0 || pos.y == shape().y-1)
            {
                ret.c = 'O';
            }
            else
            {
                ret.c = '|';
            }
        }
        else if (pos.y == 0 || pos.y == shape().y-1)
        {
            ret.c = '-';
        }
        else
        {
            taeto::RenderPixel pix = child()->pixel_at(pos - glm::uvec2({2, 1}));

            ret.c = pix.c;
            ret.fg_color = taeto::mix_colors(ret.fg_color, pix.fg_color);
            ret.bg_color = taeto::mix_colors(ret.bg_color, pix.bg_color);
            ret.bold = pix.bold;
            ret.italic = pix.italic;
            ret.underline = pix.underline;
            ret.strikethrough = pix.strikethrough;

        }
        return ret;
    };

protected:
    taeto::RenderPixel default_ = taeto::RenderPixel(' ', glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 0.75), false);
};

class WindowTest : public taeto::Object
{
public:
    WindowTest()
    {
        cb_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(1000, 1000),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        cb_->position({
            -((double)cb_->shape().x/2),
            -((double)cb_->shape().y/2),
            -10});
        cbs_ = std::make_shared<taeto::shaders::Checkerboard>();
        cb_->load_shader(cbs_);
        
        tw_ = std::make_shared<TestWindow>();
        // tw_->shape({50, 10});
        tw_->position(glm::dvec3({50, 25, -10}));

        tb_ = std::make_shared<TextBox>("This is a test.");
        tw_->child(tb_);

        // QUICK FIX
        tw_->shape({50, 10});
    };

    ~WindowTest() {};

    void load()
    {
        taeto::load_object(cb_);
        taeto::load_object(tw_, taeto::Context::kScreenSpace);
        // taeto::load_object(tb_);
    };

private:
    std::shared_ptr<taeto::Rectangle> cb_;
    std::shared_ptr<taeto::shaders::Checkerboard> cbs_;
    std::shared_ptr<TestWindow> tw_;
    std::shared_ptr<TextBox> tb_;
};

int main()
{
    taeto::debug_mode(true);
    std::shared_ptr<WindowTest> wt = std::make_shared<WindowTest>();
    taeto::load_object(wt);
    taeto::run();
}

#endif  // ASSETS_SCENES_WINDOW_TEST_H_
