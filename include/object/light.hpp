#ifndef OBJECT_LIGHT_HPP_
#define OBJECT_LIGHT_HPP_

#include "object/object.hpp"
#include "object/position.hpp"

namespace taeto
{

class Light : public Object
{
public:
    virtual taeto::Color color(taeto::Position);

    virtual taeto::Vector vector(taeto::Position);
};

}   // namespace taeto

#endif  // OBJECT_LIGHT_HPP_
