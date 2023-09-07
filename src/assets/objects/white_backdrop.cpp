#include "assets/objects/white_backdrop.hpp"

#include "components/color.h"
#include "components/render_pixel_frame.h"

namespace taeto
{

WhiteBackdrop::WhiteBackdrop()
{
    // Default position to the origin
    x_position = -100;
    y_position = -50;
    z_position = 0;

    // Set frame details
    height = 65;
    width = 200;

    respect_light_sources = true;

    current_frame = taeto::RenderPixelFrame(height, width);
    for (int i = 0; i < current_frame.height(); ++i)
        for (int j = 0; j < current_frame.width(); ++j)
            current_frame.at(i, j).background_color =
                taeto::Color(255, 255, 255);
}

}
