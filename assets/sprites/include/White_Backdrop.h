#ifndef WHITE_BACKDROP_H
#define WHITE_BACKDROP_H

#include "Sprite.h"

class White_Backdrop: public Sprite
{
    Frame default_frame;

    public:

        White_Backdrop();

        shared_ptr<Frame> get_current_frame();
};

#endif
