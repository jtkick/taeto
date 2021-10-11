#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include "Message.h"

#include <algorithm>
#include <memory>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

// Include System class
class System;

class Message_Bus
{
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // List of all systems that need to receive and send messages
    std::vector<std::shared_ptr<System>> systems;

    public:

        Message_Bus(std::shared_ptr<spdlog::logger>);

        ~Message_Bus();

        // Give pointer to system to message bus for posting messages
        void add_system(std::shared_ptr<System>);

        // Method for sending messages to systems
	    void post_message(std::shared_ptr<Message>);

        // Don't track system matching pointer given
        void remove_system(std::shared_ptr<System>);
};

#endif
