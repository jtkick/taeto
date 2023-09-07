#include "object/object.hpp"

Object::Object()
{
    x_position_ = 0;
    y_position_ = 0;
    z_position_ = 0;
}

int32_t Object::get_x_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((x_position_ >> 32) & 0x00000000FFFFFFFF);
}

int32_t Object::get_y_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((y_position_ >> 32) & 0x00000000FFFFFFFF);
}

int32_t Object::get_z_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((z_position_ >> 32) & 0x00000000FFFFFFFF);
}

int64_t Object::get_x_exact_position()
{
    return x_position_;
}

int64_t Object::get_y_exact_position()
{
    return y_position_;
}

int64_t Object::get_z_exact_position()
{
    return z_position_;
}
