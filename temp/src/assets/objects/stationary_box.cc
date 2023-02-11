#include "stationary_box.h"

#include <vector>

namespace taeto
{

StationaryBox::StationaryBox()
{
    height = 8;
    width = 16;

    x_position = 0;
    y_position = 0;
    z_position = 0;

    current_frame = taeto::Frame(height, width);

    collide = true;

    taeto::Vector v = taeto::Vector(0, 0, 120);

    taeto::Vector u = taeto::Vector(0, -90, 90);
    taeto::Vector r = taeto::Vector(90, 0, 90);
    taeto::Vector d = taeto::Vector(0, 90, 90);
    taeto::Vector l = taeto::Vector(-90, 0, 90);

    taeto::Vector ul = taeto::Vector(-90, -90, 90);
    taeto::Vector ur = taeto::Vector(90, -90, 90);
    taeto::Vector dl = taeto::Vector(-90, 90, 90);
    taeto::Vector dr = taeto::Vector(90, 90, 90);

    current_frame.set_normals({{ ul,  u, u, u, u, u, u, u, u, u, u, u, u, u, u, ur},
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               {  l,  v, v, v, v, v, v, v, v, v, v, v, v, v, v, r },
                               { dl,  d, d, d, d, d, d, d, d, d, d, d, d, d, d, dr}});

    set_color(taeto::Color(64, 64, 64));

}

void StationaryBox::set_color(taeto::Color c)
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

}   // namespace taeto
