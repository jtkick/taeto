/**
 * @file ishaped.hpp
 * @brief Definition of the shaped object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to have a shape within the game world or screen space.
 */

#ifndef OBJECT_SHAPED_HPP_
#define OBJECT_SHAPED_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/object.hpp"

namespace taeto
{

/**
 * @class IShaped
 * @brief An interface defining how an object implements the shape of an
 * object.
 */
class IShaped : public virtual Object
{
public:
    /**
     * @brief Getter for the object's shape.
     * @details This function returns the current shape of the object.
     * @return glm::uvec2& The current shape of the object.
     */
    virtual glm::uvec2& shape() { return shape_; };

    /**
     * @brief Setter for the object's shape.
     * @details This function sets the shape of the object.
     * @param shape The new shape of the object.
     */
    virtual void shape(const glm::uvec2& shape) { shape_ = shape; };

    virtual ~IShaped() = default;

protected:
    /**
     * @brief The current size of the object.
     */
    glm::uvec2 shape_ {0, 0};
};

}   // namespace taeto

#endif  // OBJECT_SHAPED_HPP_