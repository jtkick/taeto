#include <memory>

#include "taeto/engine.hpp"
#include "taeto/objects/object.hpp"
#include "taeto/objects/sprites/circle.hpp"
#include "taeto/objects/sprites/rectangle.hpp"

int main()
{
    std::shared_ptr<taeto::Rectangle> rectangle_ = std::make_shared<taeto::Rectangle>(
        glm::uvec2(100, 40),
        taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
    rectangle_->position({
        -((double)rectangle_->shape().x/2),
        -((double)rectangle_->shape().y/2),
        -10});
    taeto::load_object(rectangle_);

    taeto::RenderPixel rp = taeto::RenderPixel();
    rp.bg_color = glm::vec4(0.0f, 1.0f, 1.0f, 0.5f);

    std::shared_ptr<taeto::Circle> c_ = std::make_shared<taeto::Circle>(30, rp);
    c_->position({-16, -12, -10});
    taeto::load_object(c_);

    rp.bg_color = glm::vec4(1.0f, 0.0f, 1.0f, 0.5f);
    std::shared_ptr<taeto::Circle> m_ = std::make_shared<taeto::Circle>(30, rp);
    m_->position({-24, -4, -10});
    taeto::load_object(m_);

    rp.bg_color = glm::vec4(1.0f, 1.0f, 0.0f, 0.5f);
    std::shared_ptr<taeto::Circle> y_ = std::make_shared<taeto::Circle>(30, rp);
    y_->position({-8, -4, -10});
    taeto::load_object(y_);

    taeto::debug_mode(true);
    taeto::run();
}