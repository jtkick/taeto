#ifndef TESTS_PHYSICS_TEST_
#define TESTS_PHYSICS_TEST_

#include <memory>

#include "taeto/engine.hpp"
#include "taeto/objects/lights/directional_light.hpp"
#include "taeto/objects/sprites/circle.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/scenes/scene.hpp"
#include "taeto/shaders/checkerboard.hpp"

namespace taeto
{

class Box : public Sprite
{
public:
    Box()
    {
        shape_ = glm::uvec2(100, 30);
        black_ = RenderPixel(' ', glm::vec4(1.0, 0.0, 1.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0), false);
        clear_ = RenderPixel(
            false,
            ' ',
            glm::vec4(1.0, 0.0, 1.0, 0.0),
            glm::vec4(1.0, 0.0, 0.0, 1.0),
            false,
            false,
            false,
            false,
            glm::vec3(0.0, 0.0, 1.0),
            0.0,
            true
        );
    };

    ~Box()
    {

    };

    RenderPixel get_pixel_at(glm::uvec2 pos)
    {
        if (pos.x < 2 || pos.x > shape_.x - 3)
            return black_;
        if (pos.y > shape_.y - 2)
            return black_;
        return clear_;
    };

private:
    RenderPixel black_;
    RenderPixel clear_;
};

class PhysicsTest : public Scene
{
public:
    PhysicsTest()
    {
        cb_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(1000, 1000),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        cb_->position({
            -((double)cb_->width()/2),
            -((double)cb_->height()/2),
            -20});
        cb_->add_shader(std::make_shared<taeto::shaders::Checkerboard>());

        box_ = std::make_shared<Box>();
        box_->position({-((double)box_->width()/2),
                        -((double)box_->height()/2),
                        -10});

        for (int i = 0; i < 1; i++)
        {
            std::shared_ptr<Circle> ball = std::make_shared<Circle>(
                15,
                RenderPixel(
                    // true,
                    ' ',
                    glm::vec4(1.0, 0.0, 1.0, 0.0),
                    glm::vec4(1.0, 0.0, 0.0, 1.0),
                    false//,
                    // false,
                    // false,
                    // false,
                    // glm::vec3(0.0, 0.0, 1.0),
                    // 0.0,
                    // true
                ),
                true);
            ball->position({-10, -10, -10});
            ball->force(glm::dvec3(0.0, 2.0, 0.0));
            balls_.push_back(ball);
        }

        dl_ = std::make_shared<DirectionalLight>(glm::vec3(0.05, 0.05, 0.05), glm::vec3(0.0, 0.0, -1.0));

    };

    ~PhysicsTest()
    {

    };

    void load()
    {
        taeto::load_sprite(cb_);
        taeto::load_sprite(box_);
        for (const auto& ball : balls_)
            taeto::load_sprite(ball);
        taeto::load_light(dl_);
    }

private:
    std::shared_ptr<Rectangle> cb_;
    std::shared_ptr<Box> box_;
    std::vector<std::shared_ptr<Circle>> balls_;
    std::shared_ptr<DirectionalLight> dl_;
};

}   // namespace taeto

int main()
{
    taeto::debug_mode(true);
    taeto::load_scene(std::make_shared<taeto::PhysicsTest>());
    taeto::run();
}

#endif  // TESTS_PHYSICS_TEST_