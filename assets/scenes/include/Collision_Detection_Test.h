#ifndef COLLISION_DETECTION_TEST_H
#define COLLISION_DETECTION_TEST_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Key_Update_Message.h"
#include "Scene.h"

#include "Moving_Box.h"
#include "Stationary_Box.h"

#include <memory>

class Collision_Detection_Test : public Scene
{
    bool space_pressed;

    shared_ptr<Stationary_Box> stat_box;
    shared_ptr<Moving_Box> mov_box;

    public:

        Collision_Detection_Test();

        ~Collision_Detection_Test();

        void handle_message(shared_ptr<Message>);

        void load();
};

#endif
