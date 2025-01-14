#ifndef ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
#define ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/lights/light.hpp"

namespace taeto
{

class DirectionalLight: public taeto::Light
{
public:
    DirectionalLight();

    DirectionalLight(glm::vec3, glm::vec3);

    inline glm::vec3 color(glm::dvec3);

    inline glm::vec3 vector(glm::dvec3);

private:
    glm::vec3 color_;

    glm::vec3 vector_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_DIRECTIONAL_LIGHT_HPP_
