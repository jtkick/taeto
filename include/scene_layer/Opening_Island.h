#ifndef OPENING_ISLAND_H
#define OPENING_ISLAND_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "System.h"
#include "Palm_Tree.h"

#include <memory>

class Opening_Island : public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    public:

        Opening_Island(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        ~Opening_Island();

        void set_logger_pointer(shared_ptr<spdlog::logger>);

        void set_message_bus_pointer(shared_ptr<Message_Bus>);
};

#endif
