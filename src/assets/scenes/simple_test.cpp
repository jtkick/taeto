#include "assets/scenes/simple_test.hpp"

#include <memory>

#include "engine.hpp"
#include "assets/sprites/simple_x.hpp"

namespace taeto
{

SimpleTest::SimpleTest()
{
    s_ = std::make_shared<taeto::SimpleX>();
    s_->position({-10, 0, 0});
}

SimpleTest::~SimpleTest()
{

}

void SimpleTest::load()
{
    // Load circle
    taeto::load_sprite(s_);
}

}   // namespace taeto
