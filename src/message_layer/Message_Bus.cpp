#include "Message_Bus.h"

Message_Bus::Message_Bus()
{

}

Message_Bus::~Message_Bus()
{

}

void Message_Bus::add_system(shared_ptr<System> system)
{
    // Put on vector
    systems.push_back(system);
}

void Message_Bus::post_message(shared_ptr<Message> message)
{
    // Loop over all known systems and notify them
    for (auto it = systems.begin(); it != systems.end(); it++)
        (*it)->handle_message(message);
}

void Message_Bus::remove_system(shared_ptr<System> system)
{
    // Remove all values matching pointer
    systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
}
