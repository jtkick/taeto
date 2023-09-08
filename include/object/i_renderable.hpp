#ifndef OBJECT_I_RENDERABLE_HPP_
#define OBJECT_I_RENDERABLE_HPP_

#include "components/render_pixel.hpp"

namespace taeto
{

class IRenderable
{
public:
    /*
     * This function returns the pixel at the given position relavtive to the
     * object's position.
     */
    virtual taeto::RenderPixel get_pixel_at(uint64_t, uint64_t) = 0;

    /*
     * Returns the height of the sprite.
     */
    virtual uint64_t height() = 0;

    /*
     * Returns the axis perpendicular to how the sprite should be rendered.
     */
    virtual char plane_orientation() = 0;

    /*
     * Returns the scaling factor to adjust the size of a sprite.
     */
    // Shouldn't this be part of Frame?
    //virtual double scaling_factor() = 0;

    /*
     * Returns the width of the sprite.
     */
    virtual uint64_t width() = 0;
};

}   // namespace taeto

#endif  // OBJECT_I_RENDERABLE_HPP_
