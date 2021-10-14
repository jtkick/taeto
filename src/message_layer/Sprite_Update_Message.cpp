#include "Sprite_Update_Message.h"

Sprite_Update_Message::Sprite_Update_Message(shared_ptr<Sprite> s)
{
    sprite_ptr = s;

    id = SPRITE_UPDATE;
}

Sprite_Update_Message::~Sprite_Update_Message()
{
    id = SPRITE_UPDATE;
}

shared_ptr<Sprite> Sprite_Update_Message::get_sprite()
{
    return sprite_ptr;
}

void Sprite_Update_Message::set_sprite(shared_ptr<Sprite> s)
{
    sprite_ptr = s;
}
