#ifndef SPRITE_UPDATE_MESSAGE_H
#define SPRITE_UPDATE_MESSAGE_H

#include "Sprite.h"
#include "Message.h"

#include <memory>

class Sprite_Update_Message: public Message
{
    shared_ptr<Sprite> sprite_ptr;

    public:

        Sprite_Update_Message(shared_ptr<Sprite>);

        ~Sprite_Update_Message();

        shared_ptr<Sprite> get_sprite();

        void set_sprite(shared_ptr<Sprite>);
};

#endif
