#ifndef TESTS_PHYSICS_TEST_
#define TESTS_PHYSICS_TEST_

#include <memory>

#include "taeto/engine.hpp"
#include "taeto/objects/lights/directional_light.hpp"
#include "taeto/objects/object.hpp"
#include "taeto/objects/iphysical.hpp"
#include "taeto/objects/sprites/circle.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/shaders/checkerboard.hpp"

namespace taeto
{

class Box : public ISprite
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

    RenderPixel pixel_at(const glm::uvec2& pos)
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

// Create a circle with physics
class Ball : public Circle, public IPhysical
{
  public:
    Ball(int d, taeto::RenderPixel p, bool n) : Circle(d, p, n) { };
};


class PhysicsTest : public Object
{
public:
    PhysicsTest()
    {
        cb_ = std::make_shared<taeto::Rectangle>(
            glm::uvec2(1000, 1000),
            taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false));
        cb_->position({
            -((double)cb_->shape().x/2),
            -((double)cb_->shape().y/2),
            -20});
        cb_->load_shader(std::make_shared<taeto::shaders::Checkerboard>());

        box_ = std::make_shared<Box>();
        box_->position({-((double)box_->shape().x/2),
                        -((double)box_->shape().y/2),
                        -10});

        for (int i = 0; i < 1; i++)
        {
            std::shared_ptr<Ball> ball = std::make_shared<Ball>(
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
        taeto::load_object(cb_);
        taeto::load_object(box_);
        for (const auto& ball : balls_)
            taeto::load_object(ball);
        taeto::load_object(dl_);
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
    std::shared_ptr<taeto::PhysicsTest> pt = std::make_shared<taeto::PhysicsTest>();
    taeto::load_object(pt);
    taeto::run();
}

#endif  // TESTS_PHYSICS_TEST_