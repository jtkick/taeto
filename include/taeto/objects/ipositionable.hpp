/**
 * @file ipositionable.hpp
 * @brief Definition of the positionable object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to exist within the world of the Taeto engine. This position
 * can either describe the object position in 3D space, or its position on the
 * rendered frame, depending on how it is loaded.
 */

#ifndef OBJECT_IPOSITIONABLE_HPP_
#define OBJECT_IPOSITIONABLE_HPP_

namespace taeto
{

/**
 * @class IPositionable
 * @brief An interface defining how an object implements the ability to exist
 * in space. It provides a default implementation, since this interface should
 * rarely ever be implemented any other way.
 */
class IPositionable
{
public:
    /**
     * @brief Moves the object with the given difference.
     * @details This function moves the object in 3D space or screen space
     * relative to its current position.
     * @param diff How far to move the object in the three cardinal directions.
     */
    virtual void move(const glm::dvec3& diff) { position_ += diff; };

    /**
     * @brief Getter for the object's position.
     * @details This function returns the current position that the object
     * resides in in 3D space or screen space.
     * @return glm::dvec3& The current position of the object in 3D space.
     */
    virtual glm::dvec3 position() { return position_; };

    /**
     * @brief Setter for the object's position.
     * @details This function sets the position that the object resides in in
     * 3D space or screen space.
     * @param pos The new position of the object.
     */
    virtual void position(const glm::dvec3& pos) { position_ = pos; };

    virtual ~IPositionable() = default;

protected:
    /**
     * @brief Where the object currently resides in 3D or screen space.
     */
    glm::dvec3 position_ {0.0f, 0.0f, 0.0f};
};

}   // namespace taeto

#endif  // OBJECT_IPOSITIONABLE_HPP_