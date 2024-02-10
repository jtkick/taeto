#ifndef OBJECT_LIGHT_HPP_
#define OBJECT_LIGHT_HPP_

#include <glm/glm.hpp>

#include "object/object.hpp"

namespace taeto
{

class Light : public taeto::Object
{
public:
    Light() { };

    ~Light() { };

    virtual glm::vec3 color(glm::dvec3);

    virtual glm::vec3 vector(glm::dvec3);

    void load();

    void animate();
};

}   // namespace taeto

#endif  // OBJECT_LIGHT_HPP_
