#ifndef OBJECT_SPRITE_HPP_
#define OBJECT_SPRITE_HPP_

#include "object/position.hpp"

#include <chrono>

namespace taeto
{

class Sprite
{
public:
    /*
     * This function returns the pixel at the given position relavtive to the
     * object's position.
     */
    taeto::RenderPixel get_pixel_at(uint64_t, uint64_t) = 0;

    /*
     * Returns the height of the sprite.
     */
    uint64_t height() = 0;

    /*
     * Returns the axis perpendicular to how the sprite should be rendered.
     */
    char plane_orientation() = 0;

    /*
     * Returns the scaling factor to adjust the size of a sprite.
     */
    // Shouldn't this be part of Frame?
    //virtual double scaling_factor() = 0;

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
    uint64_t width() = 0;

    /*
     * Returns true if the object should collide with other objects that return
     * true as well.
     */
    bool collides() = 0;

    /*
     * If this object collides with others, this method determines whether or
     * not the engine will detect collisions with this object, otherwise
     * 'on_collision' will only be called when this object collides with
     * another where 'detects_collisions' returns true. This is usually true
     * for objects that move, and false for things like the floor.
     */
    bool detects_collisions() = 0;

    /*
     * Returns true if the pixel at the given position within the object should
     * collide with other objects.
     */
    bool get_collision_at(uint64_t, uint64_t) = 0;

    /*
     * Defines what happens when this object collides with the given object.
     */
    bool on_collision(std::shared_ptr<taeto::Object>) = 0;

    /*
     * Returns the given number of frames that have passed since the last time
     * this method was called.
     * @param frame_rate The number of frames per second to solve for.
     * @param refresh Whether or not to reset the timer after called.
     * @returns The number of frames that have passed.
     */
    int frame_timer(int frame_rate=30, bool refresh=true);

protected:
    // Mass of the sprite for calculating speeds
    double mass_;

    // Speeds on each individual axis
    double z_speed_;
    double y_speed_;
    double x_speed_;

    // Forces on each individual axis
    double z_force_;
    double y_force_;
    double x_force_;
};

}   // namespace taeto

#endif  // OBJECT_SPRITE_HPP_