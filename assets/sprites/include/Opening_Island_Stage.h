#ifndef OPENING_ISLAND_H
#define OPENING_ISLAND_H

#include "Sprite.h"

class Opening_Island: public Sprite
{

    vector<shared_ptr<Sprite>> collide_objects;

    public:

        Opening_Island();

        void handle_collision(shared_ptr<Sprite>);

        void add_collide_object(shared_ptr<Sprite>);

};

#endif
