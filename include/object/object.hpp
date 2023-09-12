#ifndef OBJECT_OBJECT_HPP_
#define OBJECT_OBJECT_HPP_

#include <chrono>

namespace taeto
{

class Object
{
public:
    Object();

    // Since Object is the base class for the interfaces, it needs at least one
    // virtual method to be polymorphic
    virtual ~Object() { };

    int32_t get_x_pixel_position();

    int32_t get_y_pixel_position();

    int32_t get_z_pixel_position();

    int64_t get_x_exact_position();

    int64_t get_y_exact_position();

    int64_t get_z_exact_position();

    void move(uint64_t, uint64_t, uint64_t);
    void place(uint64_t, uint64_t, uint64_t);

    // Called when the object is loaded into the engine
    // Allows object to load any necessary sub-objects
    void load();

    void animate(std::chrono::milliseconds);

protected:
    // Position on screen relative to origin
    // Top 32 bits are pixel position, bottom 32 bits are sub-pixel position
    // This allows for positions and speeds that aren't tied to frame rate
    int64_t x_position_;
    int64_t y_position_;
    int64_t z_position_;
};

}   // namespace taeto

#endif  // OBJECT_OBJECT_HPP_
