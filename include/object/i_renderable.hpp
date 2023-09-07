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
    virtual taeto::RenderPixel get_pixel_at(
        unsigned long int, unsigned long int);

    /*
     * Returns the height of the sprite.
     */
    virtual unsigned long int height();

    /*
     * Returns the axis perpendicular to how the sprite should be rendered.
     */
    virtual char plane_orientation();

    /*
     * Returns the scaling factor to adjust the size of a sprite.
     */
    virtual double scaling_factor();

    /*
     * Returns the width of the sprite.
     */
    virtual unsigned long int width();
};

}   // namespace taeto

#endif  // OBJECT_I_RENDERABLE_HPP_
