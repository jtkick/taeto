#ifndef ASSETS_SCENES_COLLISION_DETECTION_TEST_H_
#define ASSETS_SCENES_COLLISION_DETECTION_TEST_H_

#include <memory>

#include "assets/lights/directional_light.h"
#include "message_layer/Message.h"
#include "assets/objects/moving_box.h"
#include "scenes/scene.h"
#include "assets/objects/stationary_box.h"

namespace taeto
{

class CollisionDetectionTest : public Scene
{
public:
    CollisionDetectionTest();

    ~CollisionDetectionTest();

    void handle_message(shared_ptr<Message>);

    void load(int, int);

private:
    bool space_pressed_;

    shared_ptr<StationaryBox> stat_box_;

    shared_ptr<MovingBox> mov_box_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_COLLISION_DETECTION_TEST_H_
