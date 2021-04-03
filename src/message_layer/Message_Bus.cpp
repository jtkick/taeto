#include "Message_Bus.h"

Message_Bus::Message_Bus()
{

}

Message_Bus::~Message_Bus()
{

}

void Message_Bus::post_message(Message &message)
{
    // Loop over all known systems and notify them
    //for (auto it = systems.begin(); it != systems.end(); it++)
    //{
    //    it->handle_message(&message);
    //}
}
