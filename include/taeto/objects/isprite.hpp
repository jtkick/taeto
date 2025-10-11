/**
 * @file isprite.hpp
 */

#ifndef OBJECT_ISPRITE_HPP_
#define OBJECT_ISPRITE_HPP_

#include "taeto/objects/ipositionable.hpp"
#include "taeto/objects/irenderable.hpp"

namespace taeto
{

class ISprite : public virtual IPositionable, public virtual IRenderable
{

};

}   // namespace taeto

 #endif // OBJECT_ISPRITE_HPP_