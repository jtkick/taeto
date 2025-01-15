#include <chrono>
#include <memory>

#include "taeto/engine.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/lights/point_light.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/shaders/checkerboard.hpp"
#include "taeto/scenes/scene.hpp"

class HDRTest : public taeto::Scene
{
public:
    HDRTest()
    {
        rectangle_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(100, 20),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        rectangle_->position({
            -((double)rectangle_->width()/2),
            -((double)rectangle_->height()/2),
            -10});
        rectangle_->respect_light_sources(true);
        rectangle_->add_shader(std::make_shared<taeto::shaders::Checkerboard>());
        spotlight_ = std::make_shared<taeto::PointLight>(
            glm::vec3(100.0, 100.0, 100.0), 0.8);
        spotlight_->position({25, 0, 0});
        red_light_ = std::make_shared<taeto::PointLight>(
            glm::vec3(1.0, 0.0, 0.0), 0.7);
        red_light_->position({-25, 0, 0});
    };

    ~HDRTest() { };

    void load()
    {
        taeto::load_sprite(rectangle_);
        taeto::load_light(spotlight_);
        taeto::load_light(red_light_);
    };

private:
    std::shared_ptr<taeto::Rectangle> rectangle_;
    std::shared_ptr<taeto::PointLight> red_light_;
    std::shared_ptr<taeto::PointLight> spotlight_;
};

int main()
{
    taeto::load_scene(std::make_shared<HDRTest>());
    taeto::run();
}