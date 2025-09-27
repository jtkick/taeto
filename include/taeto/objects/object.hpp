/**
 * @file object.hpp
 * @brief Definition of the Taeto Object class.
 * @details This Taeto Object class is the basis for just about every other
 * object used in the Taeto engine. Because of this, it defines the methods
 * that every object must have in order to be used, as well as acting as a flag
 * class that lets systems know that this object is built for the Taeto engine.
 */

#ifndef OBJECT_OBJECT_HPP_
#define OBJECT_OBJECT_HPP_

#include <glm/glm.hpp>

namespace taeto
{

class Object
{
public:
    /**
     * @brief Called when object is loaded into the Taeto engine.
     * @details This function is overridden by sub-classes when they must do
     * additional processing once loaded into the Taeto engine, such as loading
     * in other dependent objects.
     */
    virtual void load() { };

    /**
     * @brief Called at the beginning of each frame.
     * @details This function is overridden by sub-classes when they must do
     * additional processing on each frame. It is called by the Taeto engine at
     * the beginning of each frame.
     */
    virtual void animate() { };

    virtual ~Object() = default;
};

}   // namespace taeto

#endif  // OBJECT_OBJECT_HPP_
