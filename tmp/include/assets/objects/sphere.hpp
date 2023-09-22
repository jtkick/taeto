#ifndef ASSETS_OBJECTS_SPHERE_H_
#define ASSETS_OBJECTS_SPHERE_H_

#include <memory>

#include "components/color.h"
#include "components/sprite.h"

namespace taeto
{

class Sphere: public taeto::Sprite
{
public:
    Sphere(int);

    void on_collision(std::shared_ptr<taeto::Sprite>);

private:
    set_color(taeto::Color);

    taeto::Color color_;

    std::shared_ptr<taeto::PointLight> light_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_LIGHT_BULB_H_
