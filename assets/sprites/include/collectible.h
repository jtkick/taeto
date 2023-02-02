#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "Key_Update_Message.h"
#include "Message.h"
#include "Message_Bus_Entry.h"
#include "Sprite.h"

using namespace std::chrono;

class Collectible: public Message_Bus_Entry, public Sprite
{
    // Keys pressed
    bool space = false;
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;

    // Last time animate() was run
    milliseconds last_animate_call;

    // Timer for how long to push Zero up after jump pressed
    milliseconds jump_timer;

    public:

        Collectible();

        void handle_collision(shared_ptr<Sprite>);

        void handle_message(shared_ptr<Message>);
};

#endif
