#ifndef SCENE_H
#define SCENE_H

#include "Message.h"
#include "Message_Bus_Entry.h"

#include <memory>
#include "spdlog/spdlog.h"

using namespace std;

// Include Message_Bus class
class Message_Bus;

class Scene : public Message_Bus_Entry
{
    public:

        Scene();

        virtual ~Scene();

        virtual void handle_message(shared_ptr<Message> message);

        virtual void load(int, int);
};

#endif
