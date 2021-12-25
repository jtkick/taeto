#ifndef ZERO_H
#define ZERO_H

#define FLOOR_TAG 0x01
#define WALL_TAG 0x02

#define DEFAULT_JUMP_TIME milliseconds(400)

#include "Key_Update_Message.h"
#include "Message.h"
#include "Message_Bus_Entry.h"
#include "Sprite.h"

using namespace std::chrono;

class Zero: public Message_Bus_Entry, public Sprite
{

    vector<shared_ptr<Sprite>> collide_objects;

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

        Zero();

        void handle_collision(shared_ptr<Sprite>);

        void handle_message(shared_ptr<Message>);

        void add_collide_object(shared_ptr<Sprite>);
};

#endif
