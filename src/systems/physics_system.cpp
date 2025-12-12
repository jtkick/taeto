#include "taeto/systems/physics_system.hpp"

#include <chrono>
#include <memory>

#include <glm/glm.hpp>
#include <stdexcept>
#include "spdlog/spdlog.h"

#include "taeto/objects/iphysical.hpp"
#include "taeto/tools.hpp"

#include <iostream>

namespace taeto
{

void PhysicsSystem::apply_forces(
    std::vector<std::shared_ptr<taeto::IPhysical>>& sprites)
{
    double forces_timer = (double)forces_timer_.reset() / 1000.0;

    for (const auto& sprite : sprites)
    {

        // Get any forces acting on sprite to start
        glm::dvec3 forces = sprite->force();

        // // Apply all gravity fields
        // for (const auto& field_weak_ptr : fields)
        // {
        //     // Get pointer if not dead
        //     std::shared_ptr<taeto::GravityField> field;
        //     if (!(field = field_weak_ptr.lock()))
        //         continue;

        //     forces += field->vector(sprite->position());
        // }

        // For now, just apply
        sprite->speed(sprite->speed() + (forces * forces_timer));
    }
}

void PhysicsSystem::move_objects(
    std::vector<std::shared_ptr<IPhysical>>& sprites)
{
    /////////////////////////////////////////////////////////////
    // Implement rudimentary movement for testing, since the   //
    // one taking into account collision is busted.            //
    /////////////////////////////////////////////////////////////
    double esp = 1e-7f;
    double speeds_timer = (double)speeds_timer_.reset() / 1000.0;
    for (const auto& sprite : sprites)
    {
        glm::dvec3 added_pos = sprite->speed() * speeds_timer;
        added_pos.x = glm::abs(added_pos.x) < esp ? 0.0f : added_pos.x;
        added_pos.y = glm::abs(added_pos.y) < esp ? 0.0f : added_pos.y;
        added_pos.z = glm::abs(added_pos.z) < esp ? 0.0f : added_pos.z;

        sprite->position(sprite->position() + added_pos);
    }
    return;

    //////////////////////////////////////////////////////////////
    // The following code is busted. It adds positive speed in  //
    // seemingly every direction. Maybe a rouding error? Deal   //
    // with it later.                                           //
    //////////////////////////////////////////////////////////////

    // double speeds_timer = (double)speeds_timer_.reset() / 1000.0;

    double collision_timer = 0.0;

    // This is how much we are going to increment our timer when
    // doing one step of collision detection
    double step_time = speeds_timer;
    for (const auto& sprite : sprites)
    {
        if (1.0 / glm::length(sprite->speed()) < step_time)
            step_time = 1.0 / glm::length(sprite->speed());
    }

    for (collision_timer = 0.0; collision_timer < speeds_timer; collision_timer += step_time)
    {
        for (const auto& sprite : sprites)
        {
            glm::dvec3 old_position = sprite->position();
            glm::dvec3 new_position = sprite->position() + sprite->speed() * step_time;
            sprite->position(new_position);
            
            // If the sprite moved over to a new integer position, do collision detection
            if (glm::ivec3(old_position) != glm::ivec3(new_position))
            {
                for (const auto& other : sprites)
                {
                    // Don't check if same sprite
                    if (sprite.get() == other.get())
                        continue;

                    // TODO: FIX COLLISION DETECTION
                    continue;
                    
                    // // Collision detection
                    // if (!sprite->collides_with(other))
                    //     continue;

                    // Handle collisions
                    // Start with moving sprite back to position before colliding
                    sprite->position(old_position);

                    // TODO: REFLECT SPEED ABOUT OTHER NORMAL
                    sprite->speed(glm::dvec3(0.0));

                    // Update step_time if one of the sprites sped up
                    double new_step_time = 1.0 / glm::length(sprite->speed());
                    step_time = new_step_time < step_time ? new_step_time : step_time;
                    new_step_time = 1.0 / glm::length(other->speed());
                    step_time = new_step_time < step_time ? new_step_time : step_time;
                }
            }
        }
    }


}

}   // namespace taeto
