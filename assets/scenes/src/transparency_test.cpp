#include "transparency_test.h"

TransparencyTest::TransparencyTest()
{

}

TransparencyTest::~TransparencyTest()
{

}

void TransparencyTest::load(int window_height, int window_width)
{
    // Load backdrop
    shared_ptr<White_Backdrop> backdrop = make_shared<White_Backdrop>();
    backdrop->move(-100, -32, -25);
    message_bus->post_message(make_shared<Sprite_Update_Message>(backdrop));

    // Load spotlights
    shared_ptr<Spotlight> red_light = make_shared<Spotlight>(Color(255, 0, 0), 0.8, 30);
    red_light->move(0, -7, 0);
    message_bus->post_message(make_shared<Light_Update_Message>(red_light));

    shared_ptr<Spotlight> green_light = make_shared<Spotlight>(Color(0, 255, 0), 0.8, 30);
    green_light->move(-21, 5, 0);
    message_bus->post_message(make_shared<Light_Update_Message>(green_light));

    shared_ptr<Spotlight> blue_light = make_shared<Spotlight>(Color(0, 0, 255), 0.8, 30);
    blue_light->move(21, 5, 0);
    message_bus->post_message(make_shared<Light_Update_Message>(blue_light));
}
