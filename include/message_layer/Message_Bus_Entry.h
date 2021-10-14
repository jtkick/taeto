#ifndef MESSAGE_BUS_ENTRY_H
#define MESSAGE_BUS_ENTRY_H

#include "Message.h"

#include <memory>
#include "spdlog/spdlog.h"

using namespace std;

// Include Message_Bus class
class Message_Bus;

class Message_Bus_Entry
{
    protected:

        // Engine-wide logger
        shared_ptr<spdlog::logger> logger;

        // Message bus for posting messages
        shared_ptr<Message_Bus> message_bus;

    public:

        Message_Bus_Entry();

        virtual ~Message_Bus_Entry();

        // Method for handling messages from other systems or the engine
	    virtual void handle_message(shared_ptr<Message>);

        // Connects entry to message bus
        void connect_to_bus(shared_ptr<Message_Bus>);

        // Connects entry to logger
        void connect_to_logger(shared_ptr<spdlog::logger>);
};

#endif
