#ifndef LIGHT_FILTER_TEST_H
#define LIGHT_FILTER_TEST_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "Directional_Light.h"
#include "White_Backdrop.h"
#include "light_filter.h"

#include <math.h>
#include <memory>

#define PI 3.14159265

class LightFilterTest : public Scene
{
    shared_ptr<LightFilter> c;
    shared_ptr<LightFilter> m;
    shared_ptr<LightFilter> y;

    public:

        LightFilterTest();

        ~LightFilterTest();

        void handle_message(shared_ptr<Message>);

        void load(int, int);
};

#endif
