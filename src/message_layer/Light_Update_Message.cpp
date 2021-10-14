#include "Light_Update_Message.h"

Light_Update_Message::Light_Update_Message(shared_ptr<Light> l)
{
    light_ptr = l;

    id = LIGHT_UPDATE;
}

Light_Update_Message::~Light_Update_Message()
{
    id = LIGHT_UPDATE;
}

shared_ptr<Light> Light_Update_Message::get_light()
{
    return light_ptr;
}

void Light_Update_Message::set_light(shared_ptr<Light> l)
{
    light_ptr = l;
}
