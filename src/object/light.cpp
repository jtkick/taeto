#include "object/light.hpp"

#include <glm/glm.hpp>

namespace taeto
{

glm::vec3 Light::color(glm::dvec3 p)
{
    return glm::vec3(1.0, 0.0, 1.0);
}

glm::vec3 Light::vector(glm::dvec3 p)
{
    return glm::vec3(-1.0, 0.0, 0.0);
}

void Light::load()
{

}

void Light::animate()
{

}

}   // namespace taeto
