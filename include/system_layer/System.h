#ifndef SYSTEM_H
#define SYSTEM_H

#include "Message.h"

#include <memory>

using namespace std;

class System
{

    public:

        System();

        virtual ~System();

        // Method for handling messages from other systems or the engine
	    virtual void handle_message(shared_ptr<Message>);

};

#endif
