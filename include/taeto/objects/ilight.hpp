/**
 * @file ilight.hpp
 */

#ifndef OBJECT_ILIGHT_HPP_
#define OBJECT_ILIGHT_HPP_

#include "taeto/objects/ipositionable.hpp"
#include "taeto/objects/iemissive.hpp"

namespace taeto
{

class ILight : public virtual IPositionable, public virtual IEmissive
{

};

}   // namespace taeto

 #endif // OBJECT_ILIGHT_HPP_