#ifndef MOVING_BOX_H
#define MOVING_BOX_H

#include "Sprite.h"

class Moving_Box: public Sprite
{

    public:

        Moving_Box();

        void handle_collision(shared_ptr<Sprite>);

        void set_color(Color);

};

#endif
