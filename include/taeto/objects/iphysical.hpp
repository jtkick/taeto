/**
 * @file iphysical.hpp
 * @brief Definition of the physical object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to utilize the physics system to apply forces like gravity.
 */

#ifndef OBJECT_IPHYSICAL_HPP_
#define OBJECT_IPHYSICAL_HPP_

namespace taeto
{

/**
 * @class IPhysical
 * @brief An interface defining how an object implements handling forces and
 * speeds.
 */
class IPhysical
{
public:
    /**
     * @brief Getter for the forces acting on the object.
     * @details This function returns the sum total of forces currently acting
     * on the object.
     * @return glm::dvec3 Sum of forces on the object.
     */
    virtual glm::dvec3 force() { return force_; };

    /**
     * @brief Setter for the forces acting on the object.
     * @details This function sets the forces that are acting on this object,
     * which will then be handled by the physics system.
     * @param force Forces acting on object.
     */
    virtual void force(const glm::dvec3& force) { force_ = force; };

    /**
     * @brief Getter for the object's speed.
     * @details This function returns the object's current speed in 3D space.
     * @return glm::dvec3 Current speed of the object.
     */
    virtual glm::dvec3 speed() { return speed_; };

    /**
     * @brief Setter for the object's speed.
     * @details This function sets the speed of the object in 3D space.
     * @param speed The new speed of the object.
     */
    virtual void speed(const glm::dvec3& speed) { speed_ = speed; };

private:
    /**
     * @brief The forces acting on the object.
     */
    glm::dvec3 force_;

    /**
     * @brief The speed of the object in 3D space.
     */
    glm::dvec3 speed_;
}

}   // namespace taeto

#endif  // OBJECT_IPHYSICAL_HPP_