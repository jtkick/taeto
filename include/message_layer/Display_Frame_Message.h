#ifndef DISPLAY_FRAME_MESSAGE_H
#define DISPLAY_FRAME_MESSAGE_H

#include "Frame.h"
#include "Message.h"

#include <memory>

class Display_Frame_Message: public Message
{
    shared_ptr<Frame> frame_ptr;

    public:

        Display_Frame_Message(shared_ptr<Frame>);

        ~Display_Frame_Message();

        shared_ptr<Frame> get_frame();    
};

#endif
