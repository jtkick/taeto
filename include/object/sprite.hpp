#ifndef OBJECT_SPRITE_HPP_
#define OBJECT_SPRITE_HPP_

#include "components/render_pixel.hpp"
#include "object/object.hpp"
#include "object/position.hpp"

#include <chrono>
#include <memory>

namespace taeto
{

// Maybe put these in classes?
struct Speed
{
    double z;
    double y;
    double x;

    Speed(double z_, double y_, double x_)
    {
        z = z_;
        y = y_;
        x = x_;
    }
};

struct Force
{
    double z;
    double y;
    double x;

    Force(double z_, double y_, double x_)
    {
        z = z_;
        y = y_;
        x = x_;
    }
};

class Sprite: public Object
{
public:
    Sprite() :
        mass_(0.0),
        speed_(0.0, 0.0, 0.0),
        force_(0.0, 0.0, 0.0),
        visible_(false),
        detect_collisions_(false),
        prev_timer_time_(0)
    { }

    /*
     * This function returns the pixel at the given position relavtive to the
     * object's position.
     */
    const taeto::RenderPixel& get_pixel_at(uint64_t, uint64_t);

    /*
     * Returns the height of the sprite.
     */
    uint64_t height();

    /*
     * Returns the axis perpendicular to how the sprite should be rendered.
     */
    char plane_orientation();

    /*
     * Returns the scaling factor to adjust the size of a sprite.
     */
    // Shouldn't this be part of Frame?
    //virtual double scaling_factor();

    /*
     * Sets whether or not this object can be seen in the current frame.
     * Will be set by the render system, so that the object can decide if it
     * will animate itself when it is not visible to the player.
     */
    void visible(const bool&);

    /*
     * Returns true if the sprite was visible in the last frame to be rendered
     */
    bool visible();

    /*
     * Returns the width of the sprite.
     */
    uint64_t width();

    /*
     * Returns true if the object should collide with other objects that return
     * true as well.
     */
    bool collides();

    /*
     * If this object collides with others, this method determines whether or
     * not the engine will detect collisions with this object, otherwise
     * 'on_collision' will only be called when this object collides with
     * another where 'detects_collisions' returns true. This is usually true
     * for objects that move, and false for things like the floor.
     */
    bool detect_collisions();

    /*
     * Returns true if the pixel at the given position within the object should
     * collide with other objects.
     */
    bool get_collision_at(uint64_t, uint64_t);

    /*
     * Defines what happens when this object collides with the given object.
     */
    bool on_collision(std::shared_ptr<taeto::Sprite>);

    /*
     * Returns the given number of frames that have passed since the last time
     * this method was called.
     * @param frame_rate The number of frames per second to solve for.
     * @param refresh Whether or not to reset the timer after called.
     * @returns The number of frames that have passed.
     */
    // TODO: REPLACE THIS WITH AN ACTUAL TIMING SYSTEM
    int frame_timer(int frame_rate=30, bool refresh=true);

    void mass(double);

    double mass();

    /*
     * Sets speed of the object.
     * @param speed The sprite's new speed.
     */
    void speed(const taeto::Speed& speed);

    /*
     * Applies speed to the object.
     * @param speed The speed to apply.
     */
    void apply_speed(const taeto::Speed& speed);

    /*
     * Returns the current speed of the sprite.
     */
    taeto::Speed& speed();

    /*
     * Sets force on the object.
     * @param force The sprite's new force.
     */
    void set_force(const taeto::Force& force);

    /*
     * Applies force to the object.
     * @param force The force to apply.
     */
    void apply_force(const taeto::Force& force);

    /*
     * Returns the forces currently applied to the sprite.
     */
    taeto::Force& force();

    /*
     * Animates sprite.
     */
    // TODO: MAYBE MOVE THIS TO taeto::Object?
    void animate();

protected:
    uint64_t height_;
    uint64_t width_;

    // Mass of the sprite for calculating speeds
    double mass_;

    // Sprite's speed in all directions
    taeto::Speed speed_;

    // Forces applied to sprite in all directions
    taeto::Force force_;

private:
    // Whether or not the sprite is currently visible
    bool visible_;

    // Whether or not to check for collisions with this object
    bool detect_collisions_;

    // For calculating how many frames have passed
    std::chrono::milliseconds prev_timer_time_;
};

}   // namespace taeto

#endif  // OBJECT_SPRITE_HPP_
