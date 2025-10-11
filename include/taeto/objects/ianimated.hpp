/**
 * @file ianimated.hpp
 * @brief Definition of the IAnimated class.
 * @details This class declares the methods that a class must define if it is
 * going to be animated every frame.
 */

#ifndef OBJECT_IANIMATED_HPP_
#define OBJECT_IANIMATED_HPP_

#include <glm/glm.hpp>

#include "taeto/objects/object.hpp"

namespace taeto
{

class IAnimated : public virtual Object
{
public:
    /**
     * @brief Called at the beginning of each frame.
     * @details This function is overridden by sub-classes when they must do
     * additional processing on each frame. It is called by the Taeto engine at
     * the beginning of each frame.
     */
    virtual void animate() = 0;
};

}   // namespace taeto

#endif  // OBJECT_IANIMATED_HPP_
