/**
 * @file iemissive.hpp
 * @brief Definition of the emissive object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to emit light within the world of the Taeto engine.
 */

#ifndef OBJECT_IEMISSIVE_HPP_
#define OBJECT_IEMISSIVE_HPP_

namespace taeto
{

/**
 * @class IEmissive
 * @brief An interface defining how an object implements the ability to emit
 * light into the Taeto engine world and light other objects.
 */
class IEmissive
{
public:
    /**
     * @brief Gets the color of light provided by this object.
     * @details This function takes the position of a pixel that is being
     * rendered by the engine, and returns what light that pixel should receive
     * from this light-emitting object.
     * @param pos The position of the pixel that is being rendered.
     * @return glm::vec3 The color and magnitude of the light from this object.
     */
    virtual glm::vec3 color(const glm::dvec3& pos);

    /**
     * @brief Gets the vector of the light provided by this object.
     * @details This function provides the direction that the light comes from
     * to provide light for the pixel being rendered at the given position.
     * @param pos The position of the pixel that is being rendered.
     * @return glm::vec3 The direction that the light arrives at the pixel
     * being rendered at.
     */
    virtual glm::vec3 vector(const glm::dvec3& pos);
}

}   // namespace taeto

#endif  // OBJECT_IEMISSIVE_HPP_