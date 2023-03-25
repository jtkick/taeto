#include "transparency_test.h"

#include <memory>

#include "assets/lights/spotlight.h"
#include "assets/objects/white_backdrop.h"
#include "messages/light_update_message.h"
#include "messages/sprite_update_message.h"

namespace taeto
{

TransparencyTest::TransparencyTest()
{

}

TransparencyTest::~TransparencyTest()
{

}

void TransparencyTest::load(int window_height, int window_width)
{
    // Load backdrop
    shared_ptr<WhiteBackdrop> backdrop = make_shared<WhiteBackdrop>();
    backdrop->move(-100, -32, -25);
    message_bus->post_message(make_shared<SpriteUpdateMessage>(backdrop));

    // Load spotlights
    shared_ptr<Spotlight> red_light = make_shared<Spotlight>(Color(255, 0, 0), 0.8, 30);
    red_light->move(0, -7, 0);
    message_bus->post_message(make_shared<LightUpdateMessage>(red_light));

    shared_ptr<Spotlight> green_light = make_shared<Spotlight>(Color(0, 255, 0), 0.8, 30);
    green_light->move(-21, 5, 0);
    message_bus->post_message(make_shared<LightUpdateMessage>(green_light));

    shared_ptr<Spotlight> blue_light = make_shared<Spotlight>(Color(0, 0, 255), 0.8, 30);
    blue_light->move(21, 5, 0);
    message_bus->post_message(make_shared<LightUpdateMessage>(blue_light));
}

}   // namespace taeto
