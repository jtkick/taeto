#include "components/camera.hpp"

#include <stdexcept>
#include <stdint.h>

namespace taeto
{

Camera::Camera()
{
    focal_length_ = 10;
}

Camera::~Camera()
{

}

unsigned int Camera::get_focal_length()
{
    return focal_length_;
}

void Camera::set_focal_length(unsigned int fl)
{
    if (fl == 0)
        throw std::runtime_error("Focal length must be a natural number.");

    focal_length_ = fl;
}

}   // namespace taeto
