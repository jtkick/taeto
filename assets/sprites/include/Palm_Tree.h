#ifndef PALM_TREE_H
#define PALM_TREE_H

#include "Sprite.h"

class Palm_Tree: public Sprite
{
    Frame default_frame;

    public:

        Palm_Tree();

        shared_ptr<Frame> get_current_frame();
};

#endif
