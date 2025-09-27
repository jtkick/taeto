#ifndef OBJECTS_LIGHTS_SPOTLIGHT_HPP_
#define OBJECTS_LIGHTS_SPOTLIGHT_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/iemissive.hpp"
#include "taeto/objects/ipositionable.hpp"
#include "taeto/objects/object.hpp"

namespace taeto
{

class Spotlight: public Object, public IEmissive, public IPositionable
{
public:
    /**
     * @brief Construct a new Point Light object.
     * @param color The color and intensity of the light.
     * @param fade Value for controlling the attenuation curve of the light.
     */
    Spotlight(glm::vec3 color, float fade, int radius) : color_(color),
        fade_(fade), radius_(radius) { };

    glm::vec3 color(const glm::dvec3& pos);

    glm::vec3 vector(const glm::dvec3& pos);

private:
    glm::vec3 color_ = glm::vec3(1.0, 1.0, 1.0);

    glm::vec3 vector_ = glm::vec3(0.0, 0.0, -1.0);

    unsigned int radius_ = 10;

    float fade_ = 0.9;
};

}   // namespace taeto

#endif  // OBJECTS_LIGHTS_SPOTLIGHT_HPP_
