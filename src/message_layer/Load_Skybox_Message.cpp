#include "Load_Skybox_Message.h"

Load_Skybox_Message::Load_Skybox_Message(shared_ptr<Sprite> s)
{
    sprite_ptr = s;

    id = LOAD_SKYBOX;
}

Load_Skybox_Message::~Load_Skybox_Message()
{
    id = LOAD_SKYBOX;
}

shared_ptr<Sprite> Load_Skybox_Message::get_sprite()
{
    return sprite_ptr;
}

void Load_Skybox_Message::set_sprite(shared_ptr<Sprite> s)
{
    sprite_ptr = s;
}
