#include "systems/physics_system.hpp"

#include <chrono>
#include <memory>

#include "spdlog/spdlog.h"

#include "object/sprite.hpp"

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
        double mass = sprite_ptr->mass();
        taeto::Force force = sprite_ptr->force();

        // Calculate accelerations
        double ax = force.x / mass;
        double ay = force.y / mass;
        double az = force.z / mass;

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
        taeto::Speed& speed = sprite_ptr->speed();
        speed.z += az * time_since_last_applied;
        speed.y += ay * time_since_last_applied;
        speed.x += ax * time_since_last_applied;


        // TODO: MOVE THIS TO COLLISION DETECTION
        // Update position
        taeto::Position& position = sprite_ptr->position();
        position.z(position.z() + (position.z() * time_since_last_applied));
        position.y(position.y() + (position.y() * time_since_last_applied));
        position.x(position.x() + (position.x() * time_since_last_applied));
    }
}

void PhysicsSystem::detect_collisions(
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites)
{
    // THIS SHOULD BE REWRITTEN TO HANDLE SUB-FRAME COLLISIONS, BUT RIGHT NOW
    // I JUST WANT RUDIMENTARY COLISION DETECTION, SO JUST DO THE BASICS NOW
    // TODO: SUB-FRAME COLLISION DETECTION

    // Compile list of sprites that will collide
    logger->debug("Compiling list of sprites that collide");
    std::vector<std::shared_ptr<taeto::Sprite>> sprites_that_collide;
    for (std::weak_ptr<taeto::Sprite> sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite_ptr;
        if (!(sprite_ptr = sprite_weak_ptr.lock()))
            continue;

        if (sprite_ptr->collides())
            sprites_that_collide.push_back(sprite_ptr);
    }

    // Check each sprite
    logger->debug("Checking for collisions");
    for (std::weak_ptr<taeto::Sprite> sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> spr_1;
        if (!(spr_1 = sprite_weak_ptr.lock()))
            continue;

        // Only check if detect collisions is true
        if (!spr_1->detect_collisions())
            continue;

        logger->debug("Found sprite that wants to see collisions");

        // Check collisions against every other sprite
        for (std::shared_ptr<taeto::Sprite> spr_2 : sprites_that_collide)
        {
            // Make sure they're not the same sprite
            if (spr_1 == spr_2)
                continue;

            // Do rough collision detection
            taeto::Position pos_1 = spr_1->position();
            taeto::Position pos_2 = spr_2->position();

            // x locations don't overlap
            if (((int)pos_1->x() > (int)pos_2->x() + spr_2->width()) ||
                ((int)pos_1->x() + spr_1->width()-1 < (int)pos_2->x()))
                continue;

            // y locations don't overlap
            if (((int)pos_1->y() > (int)pos_2->y() + spr_2->height()) ||
                ((int)pos_1->y() + spr_1->height()-1 < (int)pos_2->y()))
                continue;

            // Different z-plane
            if ((int)pos_1->z() != (int)pos_2->z())
                continue;

            // Now it's guaranteed that the sprites overlap in some way, so loop over each sprite's
            // collision mesh and compare to the other
            // TODO: GET TO THIS LATER

            // Notify if they collide
            spr_1->on_collision(spr_2);
        }
    }
}

}   // namespace taeto
