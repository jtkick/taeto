#ifndef COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_HPP_
#define COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_HPP_

#include <memory>

#include "object/object.hpp"

namespace taeto
{

class IPhysicalObject
{
public:
    /*
     * Returns true if the object should collide with other objects that return
     * true as well.
     */
    virtual bool collides() = 0;

    /*
     * If this object collides with others, this method determines whether or
     * not the engine will detect collisions with this object, otherwise
     * 'on_collision' will only be called when this object collides with
     * another where 'detects_collisions' returns true. This is usually true
     * for objects that move, and false for things like the floor.
     */
    virtual bool detects_collisions() = 0;

    /*
     * Returns true if the pixel at the given position within the object should
     * collide with other objects.
     */
    virtual bool get_collision_at(uint64_t, uint64_t) = 0;

    /*
     * Defines what happens when this object collides with the given object.
     */
    virtual bool on_collision(std::shared_ptr<taeto::Object>) = 0;

protected:
    // Speeds on each individual axis
    double z_speed_;
    double y_speed_;
    double x_speed_;

    // Forces on each individual axis
    double z_force_;
    double y_force_;
    double x_force_;

    // Mass of the object; in relation to the forces on the object

};

}   // namespace taeto

#endif  // COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_HPP_
