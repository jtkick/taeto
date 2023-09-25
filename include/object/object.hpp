#ifndef OBJECT_OBJECT_HPP_
#define OBJECT_OBJECT_HPP_

#include "object/position.hpp"

#include <chrono>

namespace taeto
{

class Object
{
public:
    Object() : position_(taeto::Position(0.0, 0.0, 0.0)) { };

    Object(const taeto::Position& p) : position_(p) { };

    // Since Object is the base class for the interfaces, it needs at least one
    // virtual method to be polymorphic
    ~Object() { };

    const taeto::Position& position() const;

    void position(const taeto::Position&);

    inline void move(double, double, double);
    inline void move(const taeto::Position&);

    // Called when the object is loaded into the engine
    // Allows object to load any necessary sub-objects
    virtual void load();

    virtual void animate(std::chrono::milliseconds);

protected:
    taeto::Position position_ { 0.0f, 0.0f, 0.0f };
};

}   // namespace taeto

#endif  // OBJECT_OBJECT_HPP_
