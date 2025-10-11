/**
 * @file point_light.hpp
 * @brief Definition of the point light built-in asset.
 * @details The point light is a built-in, frequently used asset for lighting a
 * scene. It defines a light object with a position in space where the closer
 * an object is to it, the more light it receives, similar to lights in the
 * real world.
 */

#ifndef OBJECTS_LIGHTS_POINT_LIGHT_HPP_
#define OBJECTS_LIGHTS_POINT_LIGHT_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/ilight.hpp"=
#include "taeto/objects/object.hpp"

namespace taeto
{

class PointLight: public ILight
{
public:
    /**
     * @brief Construct a new Point Light object.
     * @param color The color and intensity of the light.
     * @param fade Value for controlling the attenuation curve of the light.
     */
    PointLight(glm::vec3 color, float fade) : color_(color), fade_(fade) { };

    glm::vec3 color(const glm::dvec3& pos) override;

    glm::vec3 vector(const glm::dvec3& pos) override;

private:
    glm::vec3 color_ = glm::vec3(1.0, 1.0, 1.0);

    double fade_ = 0.9;
};

}   // namespace taeto

#endif  // OBJECTS_LIGHTS_POINT_LIGHT_HPP_
