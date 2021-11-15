#include "Opening_Island.h"

Opening_Island::Opening_Island()
{

}

Opening_Island::~Opening_Island()
{

}

void Opening_Island::load(int window_height, int window_width)
{
    shared_ptr<Palm_Tree> tree = make_shared<Palm_Tree>();
    //message_bus->post_message(make_shared<Sprite_Update_Message>(tree));

    zero = make_shared<Zero>();
    message_bus->post_message(make_shared<Sprite_Update_Message>(zero));

    //shared_ptr<Night_Ocean_Skybox> nos = make_shared<Night_Ocean_Skybox>();
    //message_bus->post_message(make_shared<)
    auto pcm = make_shared<Place_Camera_Message>(zero->get_x_pixel_position(),
                                                 zero->get_y_pixel_position(),
                                                 zero->get_z_pixel_position() + 10);

}

void Opening_Island::handle_message(shared_ptr<Message> message)
{
    switch (message->get_id())
    {
        case KEY_UPDATE:
        {
            logger->info("Render system received key update message.");

            shared_ptr<Key_Update_Message> kum = dynamic_pointer_cast<Key_Update_Message>(message);

            // Move camera based on key
            switch(kum->get_key())
            {
                case 'w':

                break;
            }

            // Update camera position
            auto pcm = make_shared<Place_Camera_Message>(zero->get_x_pixel_position(),
                                                         zero->get_y_pixel_position(),
                                                         zero->get_z_pixel_position() + 10);

        }
        break;
    }
}
