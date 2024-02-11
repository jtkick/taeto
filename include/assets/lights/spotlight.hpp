#ifndef ASSETS_LIGHTS_SPOTLIGHT_HPP_
#define ASSETS_LIGHTS_SPOTLIGHT_HPP_

#include <glm/glm.hpp>

#include "object/light.hpp"
#include "object/object.hpp"

namespace taeto
{

class Spotlight: public taeto::Light
{
public:
    Spotlight();

    Spotlight(glm::vec3, float, int);

    glm::vec3 color(glm::dvec3);

    glm::vec3 vector(glm::dvec3);

private:
    glm::vec3 color_;

    glm::vec3 vector_;

    unsigned int radius_;

    float fade_;
};

}   // namespace taeto

#endif  // ASSETS_LIGHTS_SPOTLIGHT_HPP_
