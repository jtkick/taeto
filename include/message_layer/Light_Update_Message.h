#ifndef LIGHT_UPDATE_MESSAGE_H
#define LIGHT_UPDATE_MESSAGE_H

#include "Light.h"
#include "Message.h"

#include <memory>

class Light_Update_Message: public Message
{
    shared_ptr<Light> light_ptr;

    public:

        Light_Update_Message(shared_ptr<Light>);

        ~Light_Update_Message();

        shared_ptr<Light> get_light();

        void set_light(shared_ptr<Light>);
};

#endif
