#include "taeto/systems/physics_system.hpp"

#include <chrono>
#include <memory>

#include <glm/glm.hpp>
#include <stdexcept>
#include "spdlog/spdlog.h"

#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/tools.hpp"





#include <iostream>

namespace taeto
{

void PhysicsSystem::apply_forces(
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
    std::vector<std::weak_ptr<taeto::GravityField>>& fields)
{
    double forces_timer = (double)forces_timer_.reset() / 1000.0;

    for (const auto& sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite;
        if (!(sprite = sprite_weak_ptr.lock()))
            continue;

        // Get any forces acting on sprite to start
        glm::dvec3 forces = sprite->force();

        // Apply all gravity fields
        for (const auto& field_weak_ptr : fields)
        {
            // Get pointer if not dead
            std::shared_ptr<taeto::GravityField> field;
            if (!(field = field_weak_ptr.lock()))
                continue;

            forces += field->vector(sprite->position());
        }

        // For now, just apply
        sprite->speed(sprite->speed() + (forces * forces_timer));
    }
}

void PhysicsSystem::apply_speeds(
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites)
{
    double speeds_timer = (double)speeds_timer_.reset() / 1000.0;

    double collision_timer = 0.0;

    // This is how much we are going to increment our timer when
    // doing one step of collision detection
    double step_time = speeds_timer;
    for (const auto& sprite_weak_ptr : sprites)
    {
        // Get pointer if not dead
        std::shared_ptr<taeto::Sprite> sprite;
        if (!(sprite = sprite_weak_ptr.lock()))
            continue;

        if (1.0 / glm::length(sprite->speed()) < step_time)
            step_time = 1.0 / glm::length(sprite->speed());
    }

    for (collision_timer = 0.0; collision_timer < speeds_timer; collision_timer += step_time)
    {
        for (const auto& sprite_weak_ptr : sprites)
        {
            // Get pointer if not dead
            std::shared_ptr<taeto::Sprite> sprite;
            if (!(sprite = sprite_weak_ptr.lock()))
                continue;

            glm::dvec3 old_position = sprite->position();
            glm::dvec3 new_position = sprite->position() + sprite->speed() * step_time;
            sprite->position(new_position);
            
            // If the sprite moved over to a new integer position, do collision detection
            if (glm::ivec3(old_position) != glm::ivec3(new_position))
            {
                for (const auto& other_weak_ptr : sprites)
                {
                    // Get pointer if not dead
                    std::shared_ptr<taeto::Sprite> other;
                    if (!(other = other_weak_ptr.lock()))
                        continue;

                    // Don't check if same sprite
                    if (sprite.get() == other.get())
                        continue;

                    // Collision detection
                    if (!sprite->collides_with(other))
                        continue;

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
