#ifndef RENDER_FRAME_MESSAGE_H
#define RENDER_FRAME_MESSAGE_H

#include "Frame.h"
#include "Message.h"

#include <memory>

class Render_Frame_Message: public Message
{
    shared_ptr<Frame> frame_ptr;

    public:

        Render_Frame_Message(shared_ptr<Frame>);

        ~Render_Frame_Message();

        shared_ptr<Frame> get_frame();
};

#endif
