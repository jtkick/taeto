#include "Message_Bus.h"
#include "System.h"

Message_Bus::Message_Bus(std::shared_ptr<spdlog::logger> l)
{
    logger = l;
}

Message_Bus::~Message_Bus()
{

}

void Message_Bus::add_system(std::shared_ptr<Message_Bus_Entry> system)
{
    // Put on vector
    logger->info("Adding system to message bus");
    systems.push_back(system);
}

void Message_Bus::post_message(std::shared_ptr<Message> message)
{
    // Loop over all known systems and notify them
    logger->info("Posting message to all systems");
    for (auto it = systems.begin(); it != systems.end(); it++)
    {
        (*it)->handle_message(message);
    }
}

void Message_Bus::remove_system(std::shared_ptr<Message_Bus_Entry> system)
{
    // Remove all values matching pointer
    logger->info("Removing system from engine");
    systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
}
