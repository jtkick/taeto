#ifndef OBJECT_SPRITE_HPP_
#define OBJECT_SPRITE_HPP_

#include <chrono>
#include <memory>

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"
#include "object/object.hpp"

namespace taeto
{

class Sprite: public Object
{
public:
    Sprite() :
        mass_(0.0),
        speed_(0.0, 0.0, 0.0),
        force_(0.0, 0.0, 0.0),
        respect_light_sources_(false),
        visible_(false),
        detect_collisions_(false),
        prev_timer_time_(0)
    { }

    /*
     * This function returns the pixel at the given position relavtive to the
     * object's position.
     */
    virtual taeto::RenderPixel get_pixel_at(glm::uvec2);

    /*
     * Returns the height of the sprite.
     */
    virtual uint height();

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
    virtual uint width();

    /*
     * Returns true if the object should collide with other objects that return
     * true as well.
     */
    virtual bool collides();

    /*
     * If this object collides with others, this method determines whether or
     * not the engine will detect collisions with this object, otherwise
     * 'on_collision' will only be called when this object collides with
     * another where 'detects_collisions' returns true. This is usually true
     * for objects that move, and false for things like the floor.
     */
    virtual bool detect_collisions();

    /*
     * Returns true if the pixel at the given position within the object should
     * collide with other objects.
     */
    virtual bool get_collision_at(glm::uvec2);

    /*
     * Defines what happens when this object collides with the given object.
     */
    virtual bool on_collision(std::shared_ptr<taeto::Sprite>);

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
    void speed(const glm::vec3& speed);

    /*
     * Returns the current speed of the sprite.
     */
    glm::vec3& speed();

    /*
     * Sets force on the object.
     * @param force The sprite's new force.
     */
    void force(const glm::vec3& force);

    /*
     * Returns the forces currently applied to the sprite.
     */
    glm::vec3& force();

    /*
     * Returns height and width of the sprite as a uvec2
     */
    glm::uvec2& shape();

    /*
     * Animates sprite.
     */
    // TODO: MAYBE MOVE THIS TO taeto::Object?
    virtual void animate();

    virtual bool respect_light_sources();

protected:
    glm::uvec2 shape_;

    // Mass of the sprite for calculating speeds
    float mass_;

    // Sprite's speed in all directions
    glm::vec3 speed_;

    // Forces applied to sprite in all directions
    glm::vec3 force_;

    bool respect_light_sources_;

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
