/**
 * @file irenderable.hpp
 * @brief Definition of the renderable object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to be rendered in the Taeto engine.
 */

#ifndef OBJECT_IRENDERABLE_HPP_
#define OBJECT_IRENDERABLE_HPP_

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

/**
 * @class IRenderable
 * @brief An interface defining how an object implements the ability to be
 * rendered on the screen as a widget or an object.
 */
class IRenderable
{
public:
    /**
     * @brief Gets the pixel at the given position.
     * @details When the engine goes to render a pixel, it determines what
     * position on the object corresponds to the relevant position in the game
     * world, and then gets it with this function. This function returns what
     * the object looks like at the given position relative to the object's
     * origin.
     * @param pos Position of pixel relative to the object's position.
     */
    virtual RenderPixel pixel_at(const glm::uvec2& pos);
};

}   // namespace taeto

 #endif // OBJECT_RENDERABLE_HPP_