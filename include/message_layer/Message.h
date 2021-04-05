#ifndef MESSAGE_H
#define MESSAGE_H

enum id_numbers { SPRITE_UPDATE,
                  LIGHT_UPDATE,
                  RENDER_FRAME,
                  DISPLAY_FRAME,
                  MOVE_CAMERA };

class Message
{
    protected:

        int id;

    public:

        Message();

        virtual ~Message();

        int get_id();

        void set_id(int);

};

#endif
