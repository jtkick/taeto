#ifndef OBJECT_CAMERA_HPP_
#define OBJECT_CAMERA_HPP_

#include "taeto/objects/ipositionable.hpp"
#include "taeto/objects/object.hpp"

namespace taeto
{

class Camera : public Object, public IPositionable
{
public:
    Camera(double l) : focal_length_(l) { };

    ~Camera();

    /**
     * Get the distance of the drawing plane from the camera.
     */
    double focal_length() { return focal_length_; };

    /**
     * Set the distance of the drawing plane from the camera.
     */
    void focal_length(double length) { focal_length_ = length; };

private:
    /**
     * Distance to the drawing plane.
     */
    double focal_length_;
};

}   // namespace taeto

#endif  // OBJECT_CAMERA_HPP_
