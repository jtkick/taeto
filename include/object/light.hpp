#ifndef OBJECT_LIGHT_HPP_
#define OBJECT_LIGHT_HPP_

#include "components/color.hpp"
#include "components/vector.hpp"
#include "object/object.hpp"
#include "object/position.hpp"

namespace taeto
{

class Light : public Object
{
public:
    Light() { };

    ~Light() { };

    taeto::Color color(taeto::Position);

    taeto::Vector vector(taeto::Position);

    void load();

    void animate();
};

}   // namespace taeto

#endif  // OBJECT_LIGHT_HPP_
