#ifndef ASSETS_SCENES_TEST_SCENE_H_
#define ASSETS_SCENES_TEST_SCENE_H_

#include <memory>

#include "message_layer/Message.h"
#include "scenes/scene.h"

namespace taeto
{

class TestScene : public Scene
{
public:
    TestScene();

    ~TestScene();

    void handle_message(shared_ptr<Message>);

    void load(int, int);

private:
    shared_ptr<Zero> zero;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_TEST_SCENE_H_
