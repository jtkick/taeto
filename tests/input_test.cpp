#include "taeto/engine.hpp"
#include "taeto/objects/ianimated.hpp"
#include "taeto/objects/isprite.hpp"

class Button : public taeto::ISprite
{
public:
    Button(char c) : c_(c), highlighted_(false) { };

    ~Button() { };

    taeto::RenderPixel pixel_at(const glm::uvec2& pos)
    {
        taeto::RenderPixel ret;
        if (highlighted_)
            ret = taeto::RenderPixel(' ', glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1), false);
        else
            ret = taeto::RenderPixel(' ', glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1), false);
        
        if (pos.x == 0)
            ret.c = '[';
        else if (pos.x == shape().x-1)
            ret.c = ']';
        else if (pos.x == shape().x / 2)
            ret.c = c_;

        return ret;
    };

    void set_highlighted(bool b)
    {
        highlighted_ = b;
    };

private:
    char c_;
    bool highlighted_;
};

class InputTest : public taeto::IAnimated
{
public:
    InputTest()
    {
        w_button_ = std::make_shared<Button>('w');
        w_button_->shape({5, 1});
        w_button_->position(glm::dvec3(20, 10, 0));
        w_button_->set_highlighted(true);
        a_button_ = std::make_shared<Button>('a');
        a_button_->shape({5, 1});
        a_button_->position({14, 12, 0});
        s_button_ = std::make_shared<Button>('s');
        s_button_->shape({5, 1});
        s_button_->position({20, 12, 0});
        d_button_ = std::make_shared<Button>('d');
        d_button_->shape({5, 1});
        d_button_->position({26, 12, 0});
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
        taeto::load_object(w_button_, taeto::Context::kScreenSpace);
        taeto::load_object(a_button_, taeto::Context::kScreenSpace);
        taeto::load_object(s_button_, taeto::Context::kScreenSpace);
        taeto::load_object(d_button_, taeto::Context::kScreenSpace);
    };

private:
    std::shared_ptr<Button> w_button_;
    std::shared_ptr<Button> a_button_;
    std::shared_ptr<Button> s_button_;
    std::shared_ptr<Button> d_button_;
};

int main()
{
    taeto::debug_mode(true);
    std::shared_ptr<InputTest> it = std::make_shared<InputTest>();
    taeto::load_object(it);
    taeto::run();
}