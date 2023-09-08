#ifndef ASSETS_LIGHTS_SPOTLIGHT_HPP_
#define ASSETS_LIGHTS_SPOTLIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/i_light.hpp"
#include "object/object.hpp"

namespace taeto
{

class Spotlight: public Object, public ILight
{
public:
    Spotlight();

    Spotlight(taeto::Color, float, int);

    inline taeto::Color light_color(
        unsigned long int, unsigned long int, unsigned long int);

    inline taeto::Vector light_vector(
        unsigned long int, unsigned long int, unsigned long int);

private:
    taeto::Color color_;

    taeto::Vector vector_;

    unsigned int radius_;

    float fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_SPOTLIGHT_HPP_
