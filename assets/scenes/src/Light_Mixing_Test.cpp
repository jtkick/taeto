#include "Light_Mixing_Test.h"

Light_Mixing_Test::Light_Mixing_Test()
{

}

Light_Mixing_Test::~Light_Mixing_Test()
{

}

void Light_Mixing_Test::load()
{
    shared_ptr<White_Backdrop> backdrop = make_shared<White_Backdrop>();
    backdrop->move(0, 0, -10);
    message_bus->post_message(make_shared<Sprite_Update_Message>(backdrop));
}
