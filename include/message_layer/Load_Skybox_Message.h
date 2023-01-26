#ifndef LOAD_SKYBOX_MESSAGE_H
#define LOAD_SKYBOX_MESSAGE_H

#include "Sprite.h"
#include "Message.h"

#include <memory>

class Load_Skybox_Message: public Message
{
    shared_ptr<Sprite> sprite_ptr;

    public:

        Load_Skybox_Message(shared_ptr<Sprite>);

        ~Load_Skybox_Message();

        shared_ptr<Sprite> get_sprite();

        void set_sprite(shared_ptr<Sprite>);
};

#endif
