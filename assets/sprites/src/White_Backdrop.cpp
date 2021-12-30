#include "White_Backdrop.h"

White_Backdrop::White_Backdrop()
{
    // Default position to the origin
    x_position = -100;
    y_position = -50;
    z_position = 0;

    // Set frame details
    height = 65;
    width = 200;

    respect_light_sources = true;

    current_frame = Frame(height, width);

    std::vector<std::vector<Color>> colors(height, std::vector<Color>(width, Color(255, 255, 255)));
    current_frame.set_background_colors(colors);
}

shared_ptr<Frame> White_Backdrop::get_current_frame()
{

    return make_shared<Frame>(current_frame);
}