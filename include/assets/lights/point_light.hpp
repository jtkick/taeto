#ifndef ASSETS_LIGHTS_POINT_LIGHT_HPP_
#define ASSETS_LIGHTS_POINT_LIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/i_light.hpp"
#include "object/object.hpp"

namespace taeto
{

class PointLight: public Object, public ILight
{
public:
    PointLight();

    PointLight(taeto::Color, float);

    inline taeto::Color light_color(
        unsigned long int, unsigned long int, unsigned long int);

    inline taeto::Vector light_vector(
        unsigned long int, unsigned long int, unsigned long int);

private:
    taeto::Color color_;

    double fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_POINT_LIGHT_HPP_
