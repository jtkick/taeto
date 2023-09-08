#include "assets/objects/normal_test.hpp"

#include "components/color.h"
#include "components/frame.h"
#include "components/vector.h"

namespace taeto
{

NormalTest::NormalTest()
{
    height = 16;
    width = 32;

    x_position = -(width/2);
    y_position = -(height/2);
    z_position = 0;

    respect_light_sources = true;
    use_normal_mapping = true;

    taeto::Frame f = taeto::Frame(height, width);

    taeto::Vector v = taeto::Vector(0, 0, 120);

    taeto::Vector u = taeto::Vector(0, -90, 90);
    taeto::Vector r = taeto::Vector(90, 0, 90);
    taeto::Vector d = taeto::Vector(0, 90, 90);
    taeto::Vector l = taeto::Vector(-90, 0, 90);

    taeto::Vector ul = taeto::Vector(-90, -90, 90);
    taeto::Vector ur = taeto::Vector(90, -90, 90);
    taeto::Vector dl = taeto::Vector(-90, 90, 90);
    taeto::Vector dr = taeto::Vector(90, 90, 90);

    taeto::Color c = taeto::Color(255, 255, 255);

    std::vector<std::vector<taeto::Color>> color_vector;

    for (int i = 0; i < height; i++)
    {
        std::vector<taeto::Color> row;
        for (int j = 0; j < width; j++)
        {
            row.push_back(c);
        }
        color_vector.push_back(row);
    }
    f.set_background_colors(color_vector);

    f.set_normals({{ ul, ul, ul, ul, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, ur, ur, ur, ur },
                   { ul, ul, ul, ul, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, u, ur, ur, ur, ur },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   {  l,  l,  l,  l, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v,  r,  r,  r,  r },
                   { dl, dl, dl, dl, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, dr, dr, dr, dr },
                   { dl, dl, dl, dl, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, dr, dr, dr, dr }});

    current_frame = f;
}

}   // namespace taeto
