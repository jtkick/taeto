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
    virtual ~Object() = default;

    virtual void load() { };
};

}   // namespace taeto

#endif  // OBJECT_OBJECT_HPP_
