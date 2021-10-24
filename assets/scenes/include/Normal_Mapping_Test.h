#ifndef NORMAL_MAPPING_TEST_H
#define NORMAL_MAPPING_TEST_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "Point_Light.h"
#include "Normal_Test.h"

#include <math.h>
#include <memory>

#define PI 3.14159265

class Normal_Mapping_Test : public Scene
{

    int distance = 50;
    float speed = 5.0;
    float current_degree = 0.0;

    shared_ptr<Normal_Test> nt;
    shared_ptr<Point_Light> pl;

    public:

        Normal_Mapping_Test();

        ~Normal_Mapping_Test();

        void handle_message(shared_ptr<Message>);

        void load();
};

#endif
