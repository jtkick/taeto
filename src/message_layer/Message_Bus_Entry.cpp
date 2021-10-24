#include "Message_Bus_Entry.h"
#include "Message_Bus.h"
#include <iostream>

Message_Bus_Entry::Message_Bus_Entry()
{

}

Message_Bus_Entry::~Message_Bus_Entry()
{

}

void Message_Bus_Entry::handle_message(shared_ptr<Message> message)
{

}

void Message_Bus_Entry::connect_to_bus(shared_ptr<Message_Bus> mb)
{
    message_bus = mb;
}

void Message_Bus_Entry::connect_to_logger(shared_ptr<spdlog::logger> l)
{
    logger = l;
}
