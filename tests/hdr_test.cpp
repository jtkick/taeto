#include <chrono>
#include <memory>

#include "taeto/engine.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/lights/point_light.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/shaders/checkerboard.hpp"
#include "taeto/objects/object.hpp"

int main()
{
    std::shared_ptr<taeto::Rectangle> rectangle_ = std::make_shared<taeto::Rectangle>(
        glm::uvec2(100, 20),
        taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
    rectangle_->position({
        -((double)rectangle_->shape().x/2),
        -((double)rectangle_->shape().y/2),
        -10});
    rectangle_->respect_light_sources(true);
    rectangle_->load_shader(std::make_shared<taeto::shaders::Checkerboard>());
    taeto::load_object(rectangle_);

    std::shared_ptr<taeto::PointLight> spotlight_ = std::make_shared<taeto::PointLight>(
        glm::vec3(200.0, 200.0, 200.0), 0.8);
    spotlight_->position({25, 0, 0});
    taeto::load_object(spotlight_);

    std::shared_ptr<taeto::PointLight> red_light_ = std::make_shared<taeto::PointLight>(
        glm::vec3(0.5, 0.0, 0.0), 0.7);
    red_light_->position({-25, 0, 0});
    taeto::load_object(red_light_);

    taeto::debug_mode(true);
    taeto::run();
}