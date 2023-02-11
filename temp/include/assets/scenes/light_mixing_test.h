#ifndef ASSETS_SCENES_LIGHT_MIXING_TEST_H_
#define ASSETS_SCENES_LIGHT_MIXING_TEST_H_

#include <memory>

#include "scenes/scene.h"

namespace taeto
{

class LightMixingTest : public Scene
{
public:
    LightMixingTest();

    ~LightMixingTest();

    void load(int, int);
};

}   // namespace taeto

#endif  // ASSETS_SCENES_LIGHT_MIXING_TEST_H_
