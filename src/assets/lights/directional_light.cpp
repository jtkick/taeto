#include "assets/lights/directional_light.hpp"

#include <glm/glm.hpp>

namespace taeto
{

DirectionalLight::DirectionalLight()
{
    color_ = glm::vec3(1.0, 1.0, 1.0);
    vector_ = glm::vec3(0.0, 0.0, -1.0);
}

DirectionalLight::DirectionalLight(glm::vec3 c, glm::vec3 v)
{
    color_ = c;
    vector_ = v;
}

inline glm::vec3 DirectionalLight::color(glm::dvec3 p)
{
    return color_;
}

inline glm::vec3 DirectionalLight::vector(glm::dvec3 p)
{
    return vector_;
}

}   // namespace taeto
