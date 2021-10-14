#ifndef KEY_UPDATE_MESSAGE_H
#define KEY_UPDATE_MESSAGE_H

#include "Message.h"

#include <memory>

class Key_Update_Message: public Message
{
    char key;

    bool pressed;

    public:

        Key_Update_Message(char, bool);

        ~Key_Update_Message();

        char get_key();

        bool is_pressed();
};

#endif
