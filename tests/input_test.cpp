#include "taeto/engine.hpp"
#include "taeto/scenes/scene.hpp"

class Button : public taeto::widgets::Widget
{
public:
    Button(char c) : c_(c), highlighted_(false)
    {
        size_ = {5, 1};

        position_ = {10, 10};
    };

    ~Button() { };

    taeto::DisplayPixelFrame render()
    {
        taeto::DisplayPixelFrame frame(size());
        frame.at({0, 0}).c = '[';
        frame.at({2, 0}).c = c_;
        frame.at({4, 0}).c = ']';

        for (int i = 0; i < 5; ++i)
        {
            frame.at({i, 0}).fg_color = highlighted_ ? glm::vec4(0.0, 0.0, 0.0, 1.0) : glm::vec4(1.0, 1.0, 1.0, 1.0);
            frame.at({i, 0}).bg_color = highlighted_ ? glm::vec4(1.0, 1.0, 1.0, 1.0) : glm::vec4(0.0, 0.0, 0.0, 1.0);
        }

        return frame;
    };

    void set_highlighted(bool b)
    {
        highlighted_ = b;
    };

private:
    char c_;
    bool highlighted_;
};

class InputTest : public taeto::Scene
{
public:
    InputTest()
    {
        w_button_ = std::make_shared<Button>('w');
        w_button_->position({20, 10});
        w_button_->set_highlighted(true);
        a_button_ = std::make_shared<Button>('a');
        a_button_->position({14, 12});
        s_button_ = std::make_shared<Button>('s');
        s_button_->position({20, 12});
        d_button_ = std::make_shared<Button>('d');
        d_button_->position({26, 12});
    };

    ~InputTest() { };

    void animate()
    {
        if (taeto::key_state('w') > 0.75)
            w_button_->set_highlighted(true);
        else
            w_button_->set_highlighted(false);
        if (taeto::key_state('a') > 0.75)
            a_button_->set_highlighted(true);
        else
            a_button_->set_highlighted(false);
        if (taeto::key_state('s') > 0.75)
            s_button_->set_highlighted(true);
        else
            s_button_->set_highlighted(false);
        if (taeto::key_state('d') > 0.75)
            d_button_->set_highlighted(true);
        else
            d_button_->set_highlighted(false);
    };

    void load()
    {
        taeto::load_widget(w_button_);
        taeto::load_widget(a_button_);
        taeto::load_widget(s_button_);
        taeto::load_widget(d_button_);
    };

private:
    std::shared_ptr<Button> w_button_;
    std::shared_ptr<Button> a_button_;
    std::shared_ptr<Button> s_button_;
    std::shared_ptr<Button> d_button_;
};

int main()
{
    taeto::set_debug_mode(true);
    taeto::load_scene(std::make_shared<InputTest>());
    taeto::run();
}