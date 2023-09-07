#include "components/camera.hpp"

#include <stdint.h>

namespace taeto
{

Camera::Camera()
{
    z_position_ = 0;
    y_position_ = 0;
    x_position_ = 0;

    focal_length_ = 10;
}

Camera::~Camera()
{

}

int32_t Camera::get_z_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((z_position_ >> 32) & 0x00000000FFFFFFFF);
}

int32_t Camera::get_y_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((y_position_ >> 32) & 0x00000000FFFFFFFF);
}

int32_t Camera::get_x_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((x_position_ >> 32) & 0x00000000FFFFFFFF);
}

int64_t Camera::get_z_exact_position()
{
    return z_position_;
}

int64_t Camera::get_y_exact_position()
{
    return y_position_;
}

int64_t Camera::get_x_exact_position()
{
    return x_position_;
}

unsigned int Camera::get_focal_length()
{
    return focal_length_;
}

void Camera::set_z_pixel_position(int32_t z)
{
    z_position_ = (int64_t)(z) << 32;
}

void Camera::set_y_pixel_position(int32_t y)
{
    y_position_ = (int64_t)(y) << 32;
}

void Camera::set_x_pixel_position(int32_t x)
{
    x_position_ = (int64_t)(x) << 32;
}

void Camera::set_z_exact_position(int64_t z)
{
    z_position_ = z;
}

void Camera::set_y_exact_position(int64_t y)
{
    y_position_ = y;
}

void Camera::set_x_exact_position(int64_t x)
{
    x_position_ = x;
}

void Camera::set_focal_length(unsigned int fl)
{
    if (fl == 0)
        throw "Focal length must be a natural number.";
        
    focal_length_ = fl;
}

}   // namespace taeto
