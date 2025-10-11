#include <chrono>
#include <memory>

#include "taeto/engine.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/objects/object.hpp"

class BasicRenderTest : public taeto::Object
{
public:
    BasicRenderTest()
    {
        rectangle_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(100, 20),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        rectangle_->position({
            -((double)rectangle_->shape().x/2),
            -((double)rectangle_->shape().y/2),
            -10});
        rectangle_->respect_light_sources(false);
    };

    ~BasicRenderTest() { };

    void load()
    {
        taeto::load_object(rectangle_);
    };

private:
    std::shared_ptr<taeto::Rectangle> rectangle_;
};

int main()
{
    std::shared_ptr<taeto::Rectangle> rectangle_ = std::make_shared<taeto::Rectangle>(
        glm::uvec2(100, 20),
        taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
    rectangle_->position({
        -((double)rectangle_->shape().x/2),
        -((double)rectangle_->shape().y/2),
        -10});
    rectangle_->respect_light_sources(false);

    taeto::debug_mode(true);
    // taeto::load_object(std::make_shared<BasicRenderTest>());
    taeto::load_object(rectangle_);
    taeto::run();
}