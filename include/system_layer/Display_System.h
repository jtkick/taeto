#ifndef DISPLAY_SYSTEM_H
#define DISPLAY_SYSTEM_H

#include "Display_Frame_Message.h"
#include "Frame.h"
#include "Message_Bus.h"
#include "System.h"

#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;

class Display_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    public:

        Display_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        ~Display_System(void);

        // Read message from engine-wide message bus
        void handle_message(shared_ptr<Message>);

    private:

        // Write entire frame to stdout
        void display_frame(shared_ptr<Frame>);
};

#endif
