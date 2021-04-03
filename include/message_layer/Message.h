#ifndef MESSAGE_H
#define MESSAGE_H

enum id_numbers { ADD_SPRITE, ADD_LIGHT, RENDER_FRAME, MOVE_CAMERA };

class Message
{
    int id;

    public:

        Message();

        ~Message();

        int get_id();

        void set_id(int);

};

#endif
