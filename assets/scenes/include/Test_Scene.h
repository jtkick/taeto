#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Message.h"
#include "Message_Bus.h"
#include "Place_Camera_Message.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "Zero.h"
#include "Test_Box.h"
#include "Directional_Light.h"

#include <memory>

using namespace std::chrono;

class Test_Scene : public Scene
{
    shared_ptr<Zero> zero;

    public:

        Test_Scene();

        ~Test_Scene();

        void handle_message(shared_ptr<Message>);

        void load(int, int);
};

#endif
