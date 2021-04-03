#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include "Message.h"

#include <vector>

class Message_Bus
{

    // List of all systems that need to receive and send messages
    //std::vector<System*> systems;

    public:

        Message_Bus();

        ~Message_Bus();

        // Method for sending messages to systems
	    void post_message(Message &);

};

#endif
