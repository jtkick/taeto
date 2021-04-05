#include "Sprite_Update_Message.h"

Sprite_Update_Message::Sprite_Update_Message(shared_ptr<Sprite> s, bool r, bool c)
{
    sprite_ptr = s;
    render = r;
    collide = c;

    id = SPRITE_UPDATE;
}

Sprite_Update_Message::~Sprite_Update_Message()
{
    render = true;
    collide = false;

    id = SPRITE_UPDATE;
}

shared_ptr<Sprite> Sprite_Update_Message::get_sprite()
{
    return sprite_ptr;
}

bool Sprite_Update_Message::get_render()
{
    return render;
}

bool Sprite_Update_Message::get_collide()
{
    return collide;
}

void Sprite_Update_Message::set_sprite(shared_ptr<Sprite> s)
{
    sprite_ptr = s;
}

void Sprite_Update_Message::set_render(bool b)
{
    render = b;
}

void Sprite_Update_Message::set_collide(bool b)
{
    collide = b;
}
