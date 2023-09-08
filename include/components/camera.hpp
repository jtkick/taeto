#ifndef COMPONENTS_CAMERA_HPP_
#define COMPONENTS_CAMERA_HPP_

#include <stdint.h>

namespace taeto
{

class Camera
{
public:

    Camera();

    ~Camera();

    /**
     * Get exact camera position.
     */
    int64_t get_z_exact_position();
    int64_t get_y_exact_position();
    int64_t get_x_exact_position();

    /**
     * Get pixel camera position.
     */
    int32_t get_z_pixel_position();
    int32_t get_y_pixel_position();
    int32_t get_x_pixel_position();

    /**
     * Get the distance of the drawing plane from the camera.
     */
    unsigned int get_focal_length();

    /**
     * Set exact camera position.
     */
    void set_z_exact_position(int64_t);
    void set_y_exact_position(int64_t);
    void set_x_exact_position(int64_t);

    /**
     * Set pixel camera position.
     */
    void set_z_pixel_position(int32_t);
    void set_y_pixel_position(int32_t);
    void set_x_pixel_position(int32_t);

    /**
     * Set the distance of the drawing plane from the camera.
     */
    void set_focal_length(unsigned int);

private:
    /**
     * Position of camera in game world.
     */
    int64_t x_position_;
    int64_t y_position_;
    int64_t z_position_;

    /**
     * Distance to the drawing plane.
     */
    unsigned int focal_length_;
};

}   // namespace taeto

#endif  // COMPONENTS_CAMERA_HPP_
