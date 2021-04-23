#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "Key_Update_Message.h"
#include "Message_Bus.h"
#include "System.h"

#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <vector>

using namespace std;

// Types of entries in input table to be updated
struct key_entry { char key; bool pressed; };

class Input_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    // Keys engine will keep an eye on
    vector<key_entry> keys;

    public:

        Input_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        ~Input_System(void);

        // Read message from engine-wide message bus
        void handle_message(shared_ptr<Message>);

    private:

        // Polls any key the engine want to keep tabs on
        void poll_inputs();
};

#endif
