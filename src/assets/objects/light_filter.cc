#include "assets/objects/light_filter.hpp"

#include "components/color.h"
#include "components/frame.h"

namespace taeto
{

LightFilter::LightFilter(Color c)
{
    height = 16;
    width = 32;

    x_position = -(width/2);
    y_position = -(height/2);
    z_position = 0;

    respect_light_sources = true;
    use_normal_mapping = true;

    Frame f = Frame(height, width);

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            f.get_pixel(i, j).background_color = c;

    current_frame = f;
}

}   // namespace taeto
