#ifndef ASSETS_SCENES_SIMPLE_TEST_H_
#define ASSETS_SCENES_SIMPLE_TEST_H_

#include <memory>

#include "assets/sprites/simple_x.hpp"
#include "scenes/scene.hpp"

namespace taeto
{

class SimpleTest : public taeto::Scene
{
public:
    SimpleTest();

    ~SimpleTest();

    void load();

private:
    std::shared_ptr<taeto::SimpleX> s_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_SIMPLE_TEST_H_
