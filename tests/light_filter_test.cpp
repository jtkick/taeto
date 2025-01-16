#include <memory>

#include "taeto/engine.hpp"
#include "taeto/objects/sprites/circle.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/scenes/scene.hpp"

class LightFilterTest : public taeto::Scene
{
public:
    LightFilterTest()
    {
        rectangle_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(100, 40),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(2.0, 2.0, 2.0, 1.0), false));
        rectangle_->position({
            -((double)rectangle_->width()/2),
            -((double)rectangle_->height()/2),
            -10});

        taeto::RenderPixel rp = taeto::RenderPixel();
        rp.bg_color = glm::vec4(0.0f, 1.0f, 1.0f, 0.75f);
        c_ = std::make_shared<taeto::Circle>(30, rp);
        c_->position({-16, -12, -10});
        rp.bg_color = glm::vec4(1.0f, 0.0f, 1.0f, 0.75f);
        m_ = std::make_shared<taeto::Circle>(30, rp);
        m_->position({-24, -4, -10});
        rp.bg_color = glm::vec4(1.0f, 1.0f, 0.0f, 0.75f);
        y_ = std::make_shared<taeto::Circle>(30, rp);
        y_->position({-8, -4, -10});
    };

    ~LightFilterTest() { };

    void load()
    {
        taeto::load_sprite(rectangle_);
        taeto::load_sprite(c_);
        taeto::load_sprite(m_);
        taeto::load_sprite(y_);
    };

private:
    std::shared_ptr<taeto::Rectangle> rectangle_;
    std::shared_ptr<taeto::Circle> c_;
    std::shared_ptr<taeto::Circle> m_;
    std::shared_ptr<taeto::Circle> y_;
};

int main()
{
    taeto::set_debug_mode(true);
    taeto::load_scene(std::make_shared<LightFilterTest>());
    taeto::run();
}