#include "Display_Frame_Message.h"

Display_Frame_Message::Display_Frame_Message(shared_ptr<Frame> f)
{
    frame_ptr = f;

    id = DISPLAY_FRAME;
}

Display_Frame_Message::~Display_Frame_Message()
{

}

shared_ptr<Frame> Display_Frame_Message::get_frame()
{
    return frame_ptr;
}
