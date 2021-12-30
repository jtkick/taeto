#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite.h"
#include "Sprite_Update_Message.h"
#include "System.h"

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Physics_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    // Sprites known to engine
    vector<shared_ptr<Sprite>> sprites;

    public:

        // Contructor
        Physics_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        // Destructor
        ~Physics_System(void);

        // Read messages from message bus
        void handle_message(shared_ptr<Message>);

    // These methods are for doing work in this system
    // They are private since all calls to do work should be done
    // using the message bus
    //private:
    public:

        // Apply physics to all known sprites
        void apply_forces();

        // Detect collisions and notify respective sprites
        void detect_collisions();
};

#endif
