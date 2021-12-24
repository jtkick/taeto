#ifndef TEST_BOX_H
#define TEST_BOX_H

#include "Sprite.h"

class Test_Box: public Sprite
{

    public:

        Test_Box(Color);

        void set_color(Color);

        void handle_collision(shared_ptr<Sprite>);

};

#endif
