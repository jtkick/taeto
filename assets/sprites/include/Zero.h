#ifndef ZERO_H
#define ZERO_H

#include "Sprite.h"

class Zero: public Sprite
{

    vector<shared_ptr<Sprite>> collide_objects;

    public:

        Zero();

        void handle_collision(shared_ptr<Sprite>);

        void add_collide_object(shared_ptr<Sprite>);

};

#endif
