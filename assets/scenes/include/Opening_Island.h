#ifndef OPENING_ISLAND_H
#define OPENING_ISLAND_H

#include "Message.h"
#include "Message_Bus.h"
#include "Sprite_Update_Message.h"
#include "Scene.h"
#include "Palm_Tree.h"

#include <memory>

class Opening_Island : public Scene
{
    public:

        Opening_Island();

        ~Opening_Island();

        void load();
};

#endif
