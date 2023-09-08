#include "assets/scenes/normal_mapping_test.hpp"

#include <math.h>

#include <chrono>
#include <memory>

#include "engine.hpp"
#include "assets/lights/point_light.hpp"
#include "assets/objects/normal_test.hpp"

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
    nt_ = std::make_shared<taeto::NormalTest>();
    nt_->move(-(nt_->get_width()/2), -(nt_->get_height()/2), -10);
    pl_ = std::make_shared<taeto::PointLight>(taeto::Color(255, 255, 255), 0.99);
    pl_->move(-10, 0, 10);
}

NormalMappingTest::~NormalMappingTest()
{

}

void NormalMappingTest::load()
{
    // Load normal box
    taeto::load_sprite(nt_);

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


    // Move light in a circle about the box
    long int x = distance_ * cos(current_degree_ * PI / 180);
    long int y = distance_ * sin(current_degree_ * PI / 180);
    pl_->place(x, y, 0);

}

}   // namespace taeto
