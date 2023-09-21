#ifndef ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
#define ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/light.hpp"
#include "object/position.hpp"

namespace taeto
{

class DirectionalLight: public Light
{
public:
    DirectionalLight();

    DirectionalLight(taeto::Color, taeto::Vector);

    inline taeto::Color color(taeto::Position);

    inline taeto::Vector vector(taeto::Position);

private:
    taeto::Color color_;

    taeto::Vector vector_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
