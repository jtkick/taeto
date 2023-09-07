#include "assets/objects/moving_box.hpp"

#include <vector>

#include "components/color.hpp"
#include "components/render_pixel.hpp"
#include "frames/render_pixel_frame.hpp"
#include "components/vector.hpp"

namespace taeto
{

MovingBox::MovingBox()
{
    int height = 8;
    int width = 16;

    current_frame_ = taeto::RenderPixelFrame(height, width);

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

    for (int i = 0; i < current_frame_.height(); ++i)
    {
        for (int j = 0; j < current_frame_.width(); ++j)
        {

        }
    }

    current_frame_.set_normals({{ ul, ul, u, u, u, u, u, u, u, u, u, u, u, u, ur, ur},
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
    for (int i = 0; i < current_frame_.height(); ++i)
        for (int j = 0; j < current_frame_.width(); ++j)
            current_frame_.at(i, j).background_color = c;
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

unsigned long int MovingBox::height()
{
    return current_frame_.height();
}

unsigned long int MovingBox::width()
{
    return current_frame_.width();
}

RenderPixel& pixel_at(unsigned long int y, unsigned long int x)
{
    return current_frame_.at(y, x);
}

}   // namespace taeto
