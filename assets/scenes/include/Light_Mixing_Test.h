#ifndef LIGHT_MIXING_TEST_H
#define LIGHT_MIXING_TEST_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Light_Update_Message.h"
#include "Scene.h"

#include "White_Backdrop.h"
#include "Spotlight.h"

#include <memory>

class Light_Mixing_Test : public Scene
{
    public:

        Light_Mixing_Test();

        ~Light_Mixing_Test();

        void load();
};

#endif
