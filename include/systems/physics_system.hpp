#ifndef SYSTEM_PHYSICS_SYSTEM_HPP_
#define SYSTEM_PHYSICS_SYSTEM_HPP_

#include <memory>

#include "spdlog/spdlog.h"

#include "object/sprite.hpp"
#include "systems/system.hpp"

namespace taeto
{

class PhysicsSystem: public System
{
public:
    PhysicsSystem();

    PhysicsSystem(std::shared_ptr<spdlog::logger>);

    ~PhysicsSystem();

    // Apply physics to all known sprites
    void apply_forces(std::vector<std::weak_ptr<taeto::Sprite>>&);

    // Detect collisions and notify respective sprites
    void detect_collisions(std::vector<std::weak_ptr<taeto::Sprite>>&);

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace taeto

#endif  // SYSTEM_PHYSICS_SYSTEM_HPP_
