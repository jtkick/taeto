#ifndef COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_H_
#define COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_H_

namespace taeto
{

class IPhysicalObject
{
public:
    virtual bool collides_with(shared_ptr<Object> sprite_ptr);

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
    
}

}   // namespace taeto

#endif COMPONENTS_OBJECT_I_PHYSICAL_OBJECT_H_
