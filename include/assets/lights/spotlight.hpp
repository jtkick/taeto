#ifndef ASSETS_LIGHTS_SPOTLIGHT_HPP_
#define ASSETS_LIGHTS_SPOTLIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/light.hpp"
#include "object/object.hpp"
#include "object/position.hpp"

namespace taeto
{

class Spotlight: public Light
{
public:
    Spotlight();

    Spotlight(taeto::Color, float, int);

    inline taeto::Color color(taeto::Position);

    inline taeto::Vector vector(taeto::Position);

private:
    taeto::Color color_;

    taeto::Vector vector_;

    unsigned int radius_;

    float fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_SPOTLIGHT_HPP_
