#ifndef ASSETS_SCENES_NORMAL_MAPPING_TEST_H_
#define ASSETS_SCENES_NORMAL_MAPPING_TEST_H_

#include <memory>

#include "assets/lights/point_light.h"
#include "assets/objects/normal_test.h"
#include "message_layer/Message.h"
#include "scenes/scene.h"

namespace taeto
{

class NormalMappingTest : public Scene
{
public:
    NormalMappingTest();

    ~NormalMappingTest();

    void handle_message(shared_ptr<Message>);

    void load(int, int);

private:
    int distance_ = 50;

    float speed_ = 5.0;

    float current_degree_ = 0.0;

    shared_ptr<NormalTest> nt_;

    shared_ptr<PointLight> pl_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_NORMAL_MAPPING_TEST_H_
