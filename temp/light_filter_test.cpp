#include "LightFilterTest.h"

LightFilterTest::LightFilterTest()
{

}

LightFilterTest::~LightFilterTest()
{

}

void LightFilterTest::load(int window_height, int window_width)
{
    // Load backdrop
    shared_ptr<White_Backdrop> backdrop = make_shared<White_Backdrop>();
    backdrop->move(-100, -32, -20);
    message_bus->post_message(make_shared<Sprite_Update_Message>(backdrop));

    // Make filters
    c = make_shared<LightFilter>(Color(0, 255, 255, 127));
    m = make_shared<LightFilter>(Color(255, 0, 255, 127));
    y = make_shared<LightFilter>(Color(255, 255, 0, 127));

    c->move(-16, -12, -10);
    m->move(-24, -4, -10);
    y->move(-8, -4, -10);

    message_bus->post_message(make_shared<Sprite_Update_Message>(y));
    message_bus->post_message(make_shared<Sprite_Update_Message>(c));
    message_bus->post_message(make_shared<Sprite_Update_Message>(m));

    // Add light
    Color c(255, 255, 255);
    Vector v(0, 0, 127);
    shared_ptr<Directional_Light> dl = make_shared<Directional_Light>(c, v);
    message_bus->post_message(make_shared<Light_Update_Message>(dl));
}

void LightFilterTest::handle_message(shared_ptr<Message> message)
{

}
