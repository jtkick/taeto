#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include "literally_whatever"

class Message_Bus
{
    public:
        
        // Method for sending messages to systems
	void post_message(Messages::message &m);

}
