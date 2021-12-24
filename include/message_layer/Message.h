#ifndef MESSAGE_H
#define MESSAGE_H

enum id_numbers { ANIMATE,
                  APPLY_FORCES,
                  DISPLAY_FRAME,
                  KEY_UPDATE,
                  LIGHT_UPDATE,
                  MOVE_CAMERA,
                  PLACE_CAMERA,
                  POLL_INPUTS,
                  PRE_RENDER,
                  RENDER_FRAME,
                  SPRITE_UPDATE };

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
