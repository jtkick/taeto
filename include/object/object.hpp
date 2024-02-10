#ifndef OBJECT_OBJECT_HPP_
#define OBJECT_OBJECT_HPP_

#include <chrono>

#include <glm/glm.hpp>

namespace taeto
{

class Object
{
public:
    Object() : position_(glm::dvec3(0.0, 0.0, 0.0)) { };

    Object(const glm::dvec3& p) : position_(p) { };

    // Since Object is the base class for the interfaces, it needs at least one
    // virtual method to be polymorphic
    ~Object() { };

    glm::dvec3& position();

    void position(const glm::dvec3&);

    inline void move(const glm::dvec3&);

    // Called when the object is loaded into the engine
    // Allows object to load any necessary sub-objects
    void load() {};

    void animate() {};

protected:
    glm::dvec3 position_ { 0.0f, 0.0f, 0.0f };
};

}   // namespace taeto

#endif  // OBJECT_OBJECT_HPP_
