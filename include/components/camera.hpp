#ifndef COMPONENTS_CAMERA_HPP_
#define COMPONENTS_CAMERA_HPP_

#include <stdint.h>

#include "object/object.hpp"

namespace taeto
{

class Camera : public Object
{
public:

    Camera();

    ~Camera();

    /**
     * Get the distance of the drawing plane from the camera.
     */
    unsigned int get_focal_length();

    /**
     * Set the distance of the drawing plane from the camera.
     */
    void set_focal_length(unsigned int);

private:
    /**
     * Distance to the drawing plane.
     */
    unsigned int focal_length_;
};

}   // namespace taeto

#endif  // COMPONENTS_CAMERA_HPP_
