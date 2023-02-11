#ifndef ASSETS_OBJECTS_MOVING_BOX_H_
#define ASSETS_OBJECTS_MOVING_BOX_H_

#include "components/sprite.h"

namespace taeto
{

class MovingBox: public Sprite
{
public:
    MovingBox();

    void handle_collision(shared_ptr<Sprite>);

    void set_color(Color);
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_MOVING_BOX_H_
