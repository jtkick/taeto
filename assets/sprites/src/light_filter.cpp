#include "light_filter.h"

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
    {
        for (int j = 0; j < width; ++j)
        {
            // f.get_pixel(i, j).c = ' ';
            // f.get_pixel(i, j).foreground_color = Color(255, 255, 255, 255);
            f.get_pixel(i, j).background_color = c;
        }
    }

    current_frame = f;
}
