#ifndef ASSETS_LIGHTS_POINT_LIGHT_HPP_
#define ASSETS_LIGHTS_POINT_LIGHT_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/lights/light.hpp"

namespace taeto
{

class PointLight: public taeto::Light
{
public:
    PointLight();

    PointLight(glm::vec3, float);

    glm::vec3 color(glm::dvec3) override;

    glm::vec3 vector(glm::dvec3) override;

private:
    glm::vec3 color_;

    double fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_POINT_LIGHT_HPP_
