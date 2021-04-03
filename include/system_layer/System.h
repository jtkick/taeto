#ifndef SYSTEM_H
#define SYSTEM_H

class System
{

    public:
        
        // Method for handling messages from other systems or the engine
	    virtual void handle_message(Messages::message &m);

}
