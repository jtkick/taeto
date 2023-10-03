#include "assets/scenes/normal_mapping_test.hpp"

#include <math.h>

#include <chrono>
#include <memory>

#include "engine.hpp"
#include "assets/lights/point_light.hpp"
#include "assets/sprites/sphere.hpp"

int const PI = 3.1415927;

namespace taeto
{

NormalMappingTest::NormalMappingTest()
{
    distance_ = 30;
    speed_ = 5.0;
    current_degree_ = 0.0;
    last_animate_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    stopwatch_ = std::chrono::milliseconds(0);
    s_ = std::make_shared<taeto::Sphere>(51);
    s_->position({-10, -((double)s_->height()/2), -((double)s_->width()/2)});
    pl_ = std::make_shared<taeto::PointLight>(taeto::Color(255, 255, 255), 0.99);
    pl_->position({-10, 0, 10});
}

NormalMappingTest::~NormalMappingTest()
{

}

void NormalMappingTest::load()
{
    // Load circle
    taeto::load_sprite(s_);

    // Load point light
    taeto::load_light(pl_);
}

void NormalMappingTest::animate()
{
    stopwatch_ += std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()) -
        last_animate_;

    last_animate_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());

    while (stopwatch_ > std::chrono::milliseconds(30))
    {
        stopwatch_ -= std::chrono::milliseconds(30);

        current_degree_ += speed_;
        current_degree_ = fmod(current_degree_, 360.0);
    }

    // num_frames =


    // Move light in a circle about the box
    double x = distance_ * cos(current_degree_ * PI / 180);
    double y = distance_ * sin(current_degree_ * PI / 180);
    pl_->position({x, y, 0});

}

}   // namespace taeto
