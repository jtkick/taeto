#include "Normal_Test.h"

Normal_Test::Normal_Test()
{
    height = 16;
    width = 32;

    x_position = -(width/2);
    y_position = -(height/2);
    z_position = 0;

    respect_light_sources = true;
    use_normal_mapping = true;

    Frame f = Frame(height, width);

    Vector v = Vector(0, 0, 120);

    Vector u = Vector(0, -90, 90);
    Vector r = Vector(90, 0, 90);
    Vector d = Vector(0, 90, 90);
    Vector l = Vector(-90, 0, 90);

    Vector ul = Vector(-90, -90, 90);
    Vector ur = Vector(90, -90, 90);
    Vector dl = Vector(-90, 90, 90);
    Vector dr = Vector(90, 90, 90);

    Color c = Color(255, 255, 255);

    vector<vector<Color>> color_vector;

    for (int i = 0; i < height; i++)
    {
        vector<Color> row;
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
