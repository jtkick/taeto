#ifndef PLACE_CAMERA_MESSAGE_H
#define PLACE_CAMERA_MESSAGE_H

#include "Message.h"

#include <memory>

class Place_Camera_Message: public Message
{
    long int x_position;
    long int y_position;
    long int z_position;

    public:

        Place_Camera_Message(long int, long int, long int);

        ~Place_Camera_Message();

        long int get_x_position();

        long int get_y_position();

        long int get_z_position();
};

#endif
