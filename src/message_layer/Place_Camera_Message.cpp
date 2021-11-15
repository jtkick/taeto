#include "Place_Camera_Message.h"

Place_Camera_Message::Place_Camera_Message(long int x, long int y, long int z)
{
    // Set global message id
    id = PLACE_CAMERA;

    // Set new location for camera
    x_position = x;
    y_position = y;
    z_position = z;
}

Place_Camera_Message::~Place_Camera_Message()
{

}

long int Place_Camera_Message::get_x_position()
{
    return x_position;
}

long int Place_Camera_Message::get_y_position()
{
    return y_position;
}

long int Place_Camera_Message::get_z_position()
{
    return z_position;
}
