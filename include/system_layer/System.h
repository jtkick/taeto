#ifndef SYSTEM_H
#define SYSTEM_H

#include "Message.h"
#include "Message_Bus_Entry.h"

#include <memory>
#include "spdlog/spdlog.h"

using namespace std;

// Include Message_Bus class
class Message_Bus;

class System : public Message_Bus_Entry
{
    public:

        System();

        virtual ~System();

        void handle_message(shared_ptr<Message> message);
};

#endif
