#include "assets/scenes/hdr_test.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "engine.hpp"
#include "assets/lights/point_light.hpp"
#include "assets/lights/spotlight.hpp"
#include "assets/sprites/checkerboard.hpp"

namespace taeto
{

HDRTest::HDRTest()
{
    checkerboard_ = std::make_shared<taeto::Checkerboard>(glm::uvec2(100, 20), glm::vec3{1.0, 1.0, 1.0});
    checkerboard_->position({
        -((double)checkerboard_->width()/2),
        -((double)checkerboard_->height()/2),
        -10});
    spotlight_ = std::make_shared<taeto::Spotlight>(
        glm::vec3(1.0, 1.0, 1.0), 0.6, 20);
    spotlight_->position({25, 0, 0});
    red_light_ = std::make_shared<taeto::PointLight>(
        glm::vec3(1.0, 0.0, 0.0), 0.7);
    red_light_->position({-25, 0, 0});
}

HDRTest::~HDRTest()
{

}

void HDRTest::load()
{
    taeto::load_sprite(checkerboard_);
    taeto::load_light(spotlight_);
    taeto::load_light(red_light_);
}

}   // namespace taeto
