/**
 * @file physics_system.hpp
 * @brief Definition of the physics system.
 * @details This file contains the definitions that a system must define in
 * order to manipulate objects such that they mimic physical world objects.
 */

#ifndef SYSTEM_PHYSICS_SYSTEM_HPP_
#define SYSTEM_PHYSICS_SYSTEM_HPP_

#include <chrono>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "taeto/objects/iphysical.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/systems/system.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

class PhysicsSystem: public System
{
public:
    PhysicsSystem() : logger_(spdlog::get("physics_system")) { };

    ~PhysicsSystem() { };

    /**
     * @brief Applies forces acting on objects in order to change their speed.
     * @param objects All of the objects to update.
     */
    void apply_forces(std::vector<std::shared_ptr<IPhysical>>& objects);

    /**
     * @brief Moves all objects according to their speeds.
     * @details This function takes all object speeds, and moves them while
     * simultaneously checking for collisions and changing their speeds
     * accordingly.
     * @param sprites All sprites that move or have collision.
     */
    void move_objects(std::vector<std::shared_ptr<IPhysical>>& sprites);

private:
    std::shared_ptr<spdlog::logger> logger_;

    Timer forces_timer_;
    Timer speeds_timer_;
};

}   // namespace taeto

#endif  // SYSTEM_PHYSICS_SYSTEM_HPP_
