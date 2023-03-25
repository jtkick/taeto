#ifndef ASSETS_SCENES_LIGHT_FILTER_TEST_H_
#define ASSETS_SCENES_LIGHT_FILTER_TEST_H_

#include <memory>

#include "message_layer/Message.h"
#include "scenes/scene.h"

namespace taeto
{

class LightFilterTest : public Scene
{
public:
    LightFilterTest();

    ~LightFilterTest();

    void handle_message(shared_ptr<Message>);

    void load(int, int);

private:
    shared_ptr<LightFilter> c;

    shared_ptr<LightFilter> m;

    shared_ptr<LightFilter> y;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_LIGHT_FILTER_TEST_H_
