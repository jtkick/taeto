#ifndef NIGHT_OCEAN_SKYBOX_H
#define NIGHT_OCEAN_SKYBOX_H

#include "Sprite.h"

class Night_Ocean_Skybox: public Sprite
{
    Frame default_frame;

    public:

        Night_Ocean_Skybox(int, int);

        shared_ptr<Frame> get_current_frame();
};

#endif
