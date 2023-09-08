#ifndef ASSETS_OBJECTS_NIGHT_OCEAN_SKYBOX_H_
#define ASSETS_OBJECTS_NIGHT_OCEAN_SKYBOX_H_

#include <memory>

#include "components/frame.h"
#include "components/sprite.h"

namespace taeto
{

class NightOceanSkybox: public Sprite
{
public:
    NightOceanSkybox(int, int);

    shared_ptr<taeto::
    Frame> get_current_frame();

private:
    taeto::Frame default_frame_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_NIGHT_OCEAN_SKYBOX_H_
