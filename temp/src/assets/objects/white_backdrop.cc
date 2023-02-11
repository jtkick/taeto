#include "white_backdrop.h"

#include "components/color.h"
#include "components/frame.h"

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

    current_frame = taeto::Frame(height, width);

    std::vector<std::vector<taeto::Color>> colors(
        height,
        std::vector<taeto::Color>(width, Color(255, 255, 255))
    );
    current_frame.set_background_colors(colors);
}

}
