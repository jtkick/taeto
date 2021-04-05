#ifndef SPRITE_UPDATE_MESSAGE_H
#define SPRITE_UPDATE_MESSAGE_H

#include "Sprite.h"
#include "Message.h"

#include <memory>

class Sprite_Update_Message: public Message
{
    shared_ptr<Sprite> sprite_ptr;
    bool render;
    bool collide;

    public:

        Sprite_Update_Message(shared_ptr<Sprite>, bool, bool);

        ~Sprite_Update_Message();

        shared_ptr<Sprite> get_sprite();

        bool get_render();

        bool get_collide();

        void set_sprite(shared_ptr<Sprite>);

        void set_render(bool);

        void set_collide(bool);
};

#endif
