#include "systems/physics_system.hpp"

#include <chrono>
#include <memory>

#include "spdlog/spdlog.h"

#include "components/sprite.h"

namespace taeto
{

PhysicsSystem::PhysicsSystem()
{

}

PhysicsSystem::PhysicsSystem(std::shared_ptr<spdlog::logger> l)
{
    logger = l;

    logger->error("Done setting up physics system.");
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::apply_forces(
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites)
{
    for (std::weak_ptr<taeto::Sprite> sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite_ptr;
        if (!(sprite_ptr = sprite_weak_ptr.lock()))
            continue;

        // Get sprite mass and forces
        double mass = sprite_ptr->get_mass();
        double fx = sprite_ptr->get_x_force();
        double fy = sprite_ptr->get_y_force();
        double fz = sprite_ptr->get_z_force();

        // Calculate accelerations
        double ax = fx / mass;
        double ay = fy / mass;
        double az = fz / mass;

        // Get current time in milliseconds
        long long current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>
            (
                std::chrono::system_clock::now().time_since_epoch()
            ).count();

        // Get time since physics last applied to this sprite
        double time_since_last_applied =
            (double)current_time -
            (double)sprite_ptr->get_time_physics_last_applied();
        sprite_ptr->set_time_physics_last_applied(current_time);

        // Get in seconds
        time_since_last_applied /= 1000;

        // Add accumulated speed to current speed
        sprite_ptr->set_x_speed(
            sprite_ptr->get_x_speed() + (ax * time_since_last_applied));
        sprite_ptr->set_y_speed(
            sprite_ptr->get_y_speed() + (ay * time_since_last_applied));
        sprite_ptr->set_z_speed(
            sprite_ptr->get_z_speed() + (az * time_since_last_applied));


        // TODO: MOVE THIS TO COLLISION DETECTION
        // Update position
        sprite_ptr->set_x_exact_position(
            sprite_ptr->get_x_exact_position() +
            (sprite_ptr->get_x_speed() * time_since_last_applied));
        sprite_ptr->set_y_exact_position(
            sprite_ptr->get_y_exact_position() +
            (sprite_ptr->get_y_speed() * time_since_last_applied));
        sprite_ptr->set_z_exact_position(
            sprite_ptr->get_z_exact_position() +
            (sprite_ptr->get_z_speed() * time_since_last_applied));
    }
}

void PhysicsSystem::detect_collisions(
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites)
{
    // THIS SHOULD BE REWRITTEN TO HANDLE SUB-FRAME COLLISIONS, BUT RIGHT NOW
    // I JUST WANT RUDIMENTARY COLISION DETECTION, SO JUST DO THE BASICS NOW

    // Compile list of sprites that will collide
    logger->debug("Compiling list of sprites that collide");
    std::vector<std::shared_ptr<taeto::Sprite>> sprites_that_collide;
    for (std::weak_ptr<taeto::Sprite> sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite_ptr;
        if (!(sprite_ptr = sprite_weak_ptr.lock()))
            continue;

        if (sprite_ptr->get_collide())
            sprites_that_collide.push_back(sprite_ptr);
    }

    // Check each sprite
    logger->debug("Checking for collisions");
    for (std::weak_ptr<taeto::Sprite> sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite_ptr;
        if (!(sprite_ptr = sprite_weak_ptr.lock()))
            continue;

        // Only check if detect collisions is true
        if (sprite_ptr->get_detect_collisions())
        {
            logger->debug("Found sprite that wants to see collisions");

            // Check collisions against every other sprite
            for (std::shared_ptr<taeto::Sprite> other_sprite_ptr : sprites_that_collide)
            {
                // Make sure they're not the same sprite
                if (sprite_ptr != other_sprite_ptr)
                {
                    // Notify if they collide
                    if (sprite_ptr->collides_with(other_sprite_ptr))
                        sprite_ptr->handle_collision(other_sprite_ptr);
                }
            }
        }
    }
}

}   // namespace taeto
