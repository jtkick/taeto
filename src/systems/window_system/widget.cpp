#include "systems/window_system/widget.hpp"

#include <glm/glm.hpp>

#include "frames/display_pixel_frame.hpp"

namespace taeto
{

Widget::Widget()
{

}

Widget::Widget(std::string name)
{
    this->name_ = name;
}

Widget::~Widget()
{

}

std::string Widget::name()
{
    return this->name_;
}

void Widget::name(std::string s)
{
    this->name_ = s;
}

// void Widget::geometry(int y, int x, int height, int width)
// {
//     this->y_ = y;
//     this->x_ = x;
//     this->height_ = height;
//     this->width_ = width;
// }

glm::ivec2 Widget::position()
{
    return position_;
}

void Widget::position(glm::ivec2 v)
{
    position_ = v;
}

glm::uvec2 Widget::size()
{
    return size_;
}

void Widget::size(glm::uvec2 v)
{
    size_ = v;
}

DisplayPixelFrame Widget::render()
{

}

}   // namespace taeto