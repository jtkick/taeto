#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "Key_Update_Message.h"
#include "Message.h"
#include "Message_Bus.h"
#include "System.h"

#include <cstdlib>
#include <SFML/Audio.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <thread>

#include <iostream>

using namespace std;

class Audio_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    shared_ptr<sf::Music> music_ptr;

    public:

        Audio_System();

        Audio_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        ~Audio_System(void);

        // Read message from engine-wide message bus
        void handle_message(shared_ptr<Message>);

        void play();

    private:

};

#endif
