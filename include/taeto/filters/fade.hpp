#ifndef FILTERS_FADE_HPP_
#define FILTERS_FADE_HPP_

#include <glm/glm.hpp>

#include "taeto/components/display_pixel.hpp"
#include "taeto/filters/filter.hpp"

namespace taeto
{

class Fade : public Filter
{
public:
    Fade(glm::vec4 color = {0.0, 0.0, 0.0, 0.0}) :
        color_(color), strength_(0.0) { };

    ~Fade() { };

    virtual DisplayPixel shade(
        DisplayPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame
    )
    {
        DisplayPixel ret = prev_pixel;
        ret.fg_color = glm::mix(prev_pixel.fg_color, color_, strength_);
        ret.bg_color = glm::mix(prev_pixel.bg_color, color_, strength_);
        return ret;
    };

    virtual void animate() { };

    void strength(double strength)
    {
        strength_ = strength;
    };

private:
    glm::vec4 color_;
    double strength_;
};

}   // namespace taeto

#endif  // FILTERS_FADE_HPP_
