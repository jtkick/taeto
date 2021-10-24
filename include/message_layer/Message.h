#ifndef MESSAGE_H
#define MESSAGE_H

enum id_numbers { ANIMATE,
                  APPLY_FORCES,
                  SPRITE_UPDATE,
                  LIGHT_UPDATE,
                  RENDER_FRAME,
                  DISPLAY_FRAME,
                  MOVE_CAMERA,
                  POLL_INPUTS,
                  KEY_UPDATE};

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
