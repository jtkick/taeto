#include "Key_Update_Message.h"

Key_Update_Message::Key_Update_Message(char c, bool b)
{
    key = c;
    pressed = b;

    id = KEY_UPDATE;
}

Key_Update_Message::~Key_Update_Message()
{

}

char Key_Update_Message::get_key()
{
    return key;
}

bool Key_Update_Message::is_pressed()
{
    return pressed;
}
