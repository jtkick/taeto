#ifndef SYSTEM_H
#define SYSTEM_H

#include "Message.h"

#include <memory>
#include "spdlog/spdlog.h"

using namespace std;

// Include Message_Bus class
class Message_Bus;

class System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;
    
    public:

        System();

        virtual ~System();

        // Method for handling messages from other systems or the engine
	    virtual void handle_message(shared_ptr<Message>);

};

#endif
