#include "test_box.h"

#include <memory>

#include "components/color.h"
#include "components/sprite.h"

namespace taeto
{

TestBox::TestBox(taeto::Color c)
{
    height = 8;
    width = 16;

    x_position = 0;
    y_position = 0;
    z_position = 0;

    current_frame = taeto::Frame(height, width);

    collide = true;

    set_color(c);

    respect_light_sources = true;

}

void TestBox::set_color(taeto::Color c)
{
    std::vector<std::vector<taeto::Color>> color_vector;

    // Dull color
    taeto::Color dc = taeto::Color(c.red / 2, c.green / 2, c.blue / 2);

    for (int y = 0; y < height; y++)
    {
        std::vector<taeto::Color> row;
        for (int x = 0; x < width; x++)
        {
            if ( (x % 8 < 4) != (y % 4 < 2) )
            {
                row.push_back(c);
            }
            else
            {
                row.push_back(dc);
            }
        }
        color_vector.push_back(row);
    }

    current_frame.set_background_colors(color_vector);
}

void TestBox::handle_collision(std::shared_ptr<taeto::Sprite> other_sprite)
{

}

}   // namespace taeto
