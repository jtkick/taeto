#ifndef FILTERS_BLUR_HPP_
#define FILTERS_BLUR_HPP_

#include <glm/glm.hpp>

#include "taeto/components/display_pixel.hpp"
#include "taeto/filters/filter.hpp"

namespace taeto
{

class Blur : public Filter
{
public:
    Blur() : strength_(0.0) { };

    ~Blur() { };

    virtual DisplayPixel shade(
        DisplayPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame
    )
    {
        DisplayPixel ret = prev_pixel;
        ret.bg_color = glm::mix(
            prev_pixel.fg_color, prev_pixel.bg_color, strength_);
        return ret;
    };

    virtual void animate() { };

    void strength(double strength)
    {
        strength_ = strength;
    };

private:
    double strength_;
};

}   // namespace taeto

#endif  // FILTERS_BLUR_HPP_
