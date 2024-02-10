#include "object/object.hpp"

#include <glm/glm.hpp>

namespace taeto
{

glm::dvec3& Object::position()
{
    return position_;
}

void Object::position(const glm::dvec3& p)
{
    position_ = p;
}

void Object::move(const glm::dvec3& diff)
{
    position_ += diff;
}

}   // namespace taeto
