#ifndef OPENING_ISLAND_H
#define OPENING_ISLAND_H

#include "Message.h"
#include "Message_Bus.h"
#include "Key_Update_Message.h"
#include "Place_Camera_Message.h"
#include "Sprite_Update_Message.h"
#include "Scene.h"

#include "Palm_Tree.h"
#include "Zero.h"
#include "Night_Ocean_Skybox.h"

#include "Normal_Test.h"

#include <memory>

class Opening_Island : public Scene
{
    shared_ptr<Zero> zero;

    public:

        Opening_Island();

        ~Opening_Island();

        void handle_message(shared_ptr<Message>);

        void load(int, int);
};

#endif