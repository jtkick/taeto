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
#include "Test_Box.h"
#include "Directional_Light.h"

#include <memory>

class Test_Scene : public Scene
{
    shared_ptr<Zero> zero;

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
