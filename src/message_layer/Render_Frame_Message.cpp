#include "Render_Frame_Message.h"

Render_Frame_Message::Render_Frame_Message(shared_ptr<Frame> f)
{
    frame_ptr = f;

    id = RENDER_FRAME;
}

Render_Frame_Message::~Render_Frame_Message()
{

}

shared_ptr<Frame> Render_Frame_Message::get_frame()
{
    return frame_ptr;
}
