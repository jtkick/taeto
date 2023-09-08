#ifndef ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
#define ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/i_light.hpp"
#include "object/object.hpp"

namespace taeto
{

class DirectionalLight: public Object, public ILight
{
public:
    DirectionalLight();

    DirectionalLight(taeto::Color, taeto::Vector);

    inline taeto::Color light_color(
        unsigned long int, unsigned long int, unsigned long int);

    inline taeto::Vector light_vector(
        unsigned long int, unsigned long int, unsigned long int);

private:
    taeto::Color color_;

    taeto::Vector vector_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
