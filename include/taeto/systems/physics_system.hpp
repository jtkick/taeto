#ifndef SYSTEM_PHYSICS_SYSTEM_HPP_
#define SYSTEM_PHYSICS_SYSTEM_HPP_

#include <chrono>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "taeto/objects/object.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/systems/system.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

class GravityField : public Object
{
public:
    GravityField() { };

    ~GravityField() { };

    glm::dvec3 vector(const glm::dvec3& position) { };
};

class DirectionalGravityField : public GravityField
{
public:
    DirectionalGravityField(glm::dvec3 vector = glm::dvec3(0.0, 0.0, 0.0)) : vector_(vector) { };

    ~DirectionalGravityField() { };

    glm::dvec3 vector(const glm::dvec3& position) { return vector_; };

private:
    glm::dvec3 vector_;
};

class PhysicsSystem: public System
{
public:
    PhysicsSystem() : logger_(spdlog::get("physics_system")) { };

    ~PhysicsSystem() { };

    // Apply physics to all known sprites
    void apply_forces(
        std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
        std::vector<std::weak_ptr<taeto::GravityField>>& fields);

    void apply_speeds(
        std::vector<std::weak_ptr<taeto::Sprite>>& sprites);

private:
    std::shared_ptr<spdlog::logger> logger_;

    Timer forces_timer_;
    Timer speeds_timer_;
};

}   // namespace taeto

#endif  // SYSTEM_PHYSICS_SYSTEM_HPP_
