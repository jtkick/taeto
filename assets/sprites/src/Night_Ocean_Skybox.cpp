#include "Night_Ocean_Skybox.h"

Night_Ocean_Skybox::Night_Ocean_Skybox(int h, int w)
{
    // Default position to the origin
    x_position = 0;
    y_position = 0;
    z_position = 0;

    // Set frame details
    height = h;
    width = w;

    default_frame = Frame(height, width);

    // Add ocean color
    Color ocean_blue = Color(25, 42, 69);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Pixel& pixel = default_frame.get_pixel(i, j);
            pixel.set_background_color(ocean_blue);
        }
    }

}

shared_ptr<Frame> Night_Ocean_Skybox::get_current_frame()
{
    return make_shared<Frame>(default_frame);
}
