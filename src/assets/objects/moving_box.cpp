#include "assets/objects/moving_box.hpp"

#include <vector>

#include "components/color.h"
#include "components/frame.h"
#include "components/vector.h"

namespace taeto
{

MovingBox::MovingBox()
{
    height = 8;
    width = 16;

    x_position = 0;
    y_position = 0;
    z_position = 0;

    current_frame = taeto::Frame(height, width);

    collide = true;
    detect_collisions = true;

    taeto::Vector v = taeto::Vector(0, 0, 120);

    taeto::Vector u = taeto::Vector(0, -90, 90);
    taeto::Vector r = taeto::Vector(90, 0, 90);
    taeto::Vector d = taeto::Vector(0, 90, 90);
    taeto::Vector l = taeto::Vector(-90, 0, 90);

    taeto::Vector ul = taeto::Vector(-90, -90, 90);
    taeto::Vector ur = taeto::Vector(90, -90, 90);
    taeto::Vector dl = taeto::Vector(-90, 90, 90);
    taeto::Vector dr = taeto::Vector(90, 90, 90);

    current_frame.set_normals({{ ul, ul, u, u, u, u, u, u, u, u, u, u, u, u, ur, ur},
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               { dl, dl, d, d, d, d, d, d, d, d, d, d, d, d, dr, dr}});

    set_color(taeto::Color(0, 255, 0));
}

void MovingBox::set_color(taeto::Color c)
{
    std::vector<std::vector<taeto::Color>> color_vector;

    for (int i = 0; i < height; i++)
    {
        std::vector<taeto::Color> row;
        for (int j = 0; j < width; j++)
            row.push_back(c);

        color_vector.push_back(row);
    }

    current_frame.set_background_colors(color_vector);
}

void MovingBox::handle_collision(std::shared_ptr<Sprite> sprite_ptr)
{
    set_color(taeto::Color(255, 0, 0));

    for (int y = 0; y < current_frame.get_height(); ++y)
        for (int x = 0; x < current_frame.get_width(); ++x)
            current_frame.get_pixel(y, x).foreground_color = taeto::Color(255, 0, 0);

    // Move right
    while (this->collides_with(sprite_ptr))
        this->move(1, 0, 0);
}

}   // namespace taeto
