#include "taeto/objects/camera.hpp"

#include <stdexcept>
#include <stdint.h>

namespace taeto
{

Camera::Camera()
{
    focal_length_ = 10;
}

Camera::Camera(int fl)
{
    focal_length_ = fl;
}

Camera::~Camera()
{

}

unsigned int Camera::focal_length()
{
    return focal_length_;
}

void Camera::focal_length(unsigned int fl)
{
    if (fl == 0)
        throw std::runtime_error("Focal length must be a natural number.");

    focal_length_ = fl;
}

}   // namespace taeto
