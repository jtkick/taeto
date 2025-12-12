#ifndef FILTERS_FILTER_HPP_
#define FILTERS_FILTER_HPP_

#include <glm/glm.hpp>

#include "taeto/components/display_pixel.hpp"
#include "taeto/objects/ianimated.hpp"

namespace taeto
{

class Filter : public IAnimated
{
public:
    Filter() { };

    ~Filter() { };

    virtual DisplayPixel shade(
        DisplayPixel prev_pixel,
        glm::uvec2 frame_shape,
        glm::uvec2 pos_in_frame
    ) { };

    virtual void animate() { };
};

}   // namespace taeto

#endif  // FILTERS_FILTER_HPP_
