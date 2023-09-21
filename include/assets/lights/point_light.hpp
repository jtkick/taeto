#ifndef ASSETS_LIGHTS_POINT_LIGHT_HPP_
#define ASSETS_LIGHTS_POINT_LIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/light.hpp"
#include "object/position.hpp"

namespace taeto
{

class PointLight: public Light
{
public:
    PointLight();

    PointLight(taeto::Color, float);

    inline taeto::Color color(taeto::Position);

    inline taeto::Vector vector(taeto::Position);

private:
    taeto::Color color_;

    double fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_POINT_LIGHT_HPP_
