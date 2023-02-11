#include "moving_box.h"

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

    current_frame = Frame(height, width);

    collide = true;
    detect_collisions = true;

    Vector v = Vector(0, 0, 120);

    Vector u = Vector(0, -90, 90);
    Vector r = Vector(90, 0, 90);
    Vector d = Vector(0, 90, 90);
    Vector l = Vector(-90, 0, 90);

    Vector ul = Vector(-90, -90, 90);
    Vector ur = Vector(90, -90, 90);
    Vector dl = Vector(-90, 90, 90);
    Vector dr = Vector(90, 90, 90);

    current_frame.set_normals({{ ul, ul, u, u, u, u, u, u, u, u, u, u, u, u, ur, ur},
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               {  l,  l, v, v, v, v, v, v, v, v, v, v, v, v,  r, r },
                               { dl, dl, d, d, d, d, d, d, d, d, d, d, d, d, dr, dr}});

    set_color(Color(0, 255, 0));
}

void MovingBox::set_color(Color c)
{
    vector<vector<Color>> color_vector;

    for (int i = 0; i < height; i++)
    {
        vector<Color> row;
        for (int j = 0; j < width; j++)
            row.push_back(c);

        color_vector.push_back(row);
    }

    current_frame.set_background_colors(color_vector);
}


void MovingBox::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    set_color(Color(255, 0, 0));

    for (int y = 0; y < current_frame.get_height(); ++y)
        for (int x = 0; x < current_frame.get_width(); ++x)
            current_frame.get_pixel(y, x).foreground_color = Color(255, 0, 0);

    // Move right
    while (this->collides_with(sprite_ptr))
        this->move(1, 0, 0);
}

}   // namespace taeto
