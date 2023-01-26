#ifndef TRANSPARENCY_TEST_H
#define TRANSPARENCY_TEST_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "White_Backdrop.h"
#include "Spotlight.h"

#include <memory>

class TransparencyTest : public Scene
{
    public:

        TransparencyTest();

        ~TransparencyTest();

        void load(int, int);
};

#endif
