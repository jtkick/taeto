#include "object/light.hpp"

#include "components/color.hpp"
#include "components/vector.hpp"

namespace taeto
{

taeto::Color Light::color(taeto::Position p)
{
    return taeto::Color(255, 0, 255);
}

taeto::Vector Light::vector(taeto::Position p)
{
    return taeto::Vector(-127, 0, 0);
}

void Light::load()
{

}

void Light::animate()
{

}

}   // namespace taeto
