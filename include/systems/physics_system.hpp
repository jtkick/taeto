#ifndef SYSTESM_PHYSICS_SYSTEM_H_
#define SYSTESM_PHYSICS_SYSTEM_H_

#include <memory>

#include "spdlog/spdlog.h"

#include "components/sprite.h"
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
    void apply_forces();

    // Detect collisions and notify respective sprites
    void detect_collisions();

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Sprites known to engine
    std::vector<std::shared_ptr<taeto::Sprite>> sprites;
};

}   // namespace taeto

#endif  // SYSTESM_PHYSICS_SYSTEM_H_
