#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Message.h"
#include "Message_Bus.h"
#include "Key_Update_Message.h"
#include "Place_Camera_Message.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "Zero.h"
#include "Normal_Test.h"
#include "Directional_Light.h"

#include <memory>

class Test_Scene : public Scene
{
    shared_ptr<Zero> zero;

    const uint64_t FLOOR = 0x01;
    const uint64_t WALL = 0x02;

    // Keys pressed
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;

    public:

        Test_Scene();

        ~Test_Scene();

        void handle_message(shared_ptr<Message>);

        void load(int, int);
};

#endif
