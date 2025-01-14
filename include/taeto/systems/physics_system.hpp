#ifndef SYSTEM_PHYSICS_SYSTEM_HPP_
#define SYSTEM_PHYSICS_SYSTEM_HPP_

#include <chrono>
#include <memory>
#include <vector>

#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/systems/system.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

class PhysicsSystem: public System
{
public:
    PhysicsSystem() : time_physics_last_applied_(ms_since_epoch()) { };

    ~PhysicsSystem() { };

    // Apply physics to all known sprites
    void apply_forces(std::vector<std::weak_ptr<taeto::Sprite>>&);

    // Detect collisions and notify respective sprites
    void detect_collisions(std::vector<std::weak_ptr<taeto::Sprite>>&);

private:
    std::chrono::milliseconds time_physics_last_applied_;
};

}   // namespace taeto

#endif  // SYSTEM_PHYSICS_SYSTEM_HPP_
