#ifndef PhysicsSystem_H
#define PhysicsSystem_H

#include "message_layer/Message.h"
#include "systems/message_bus.h"
#include "components/sprite.h"
#include "message_layer/Sprite_Update_Message.h"
#include "systems/system.h"

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class PhysicsSystem: public System
{
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    std::shared_ptr<Message_Bus> message_bus;

    // Sprites known to engine
    std::vector<std::shared_ptr<taeto::Sprite>> sprites;

    public:

        // Contructor
        PhysicsSystem();

        PhysicsSystem(std::shared_ptr<spdlog::logger>, std::shared_ptr<Message_Bus>);

        // Destructor
        ~PhysicsSystem(void);

        // Read messages from message bus
        void handle_message(std::shared_ptr<Message>);

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
