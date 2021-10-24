#include "Collision_Detection_Test.h"

Collision_Detection_Test::Collision_Detection_Test()
{
    space_pressed = false;
}

Collision_Detection_Test::~Collision_Detection_Test()
{

}

void Collision_Detection_Test::load()
{
    // Load stationary box
    stat_box = make_shared<Stationary_Box>();
    stat_box->move(-40, -stat_box->get_height()/2, -10);
    message_bus->post_message(make_shared<Sprite_Update_Message>(stat_box));

    // Load moving box
    mov_box = make_shared<Moving_Box>();
    mov_box->move(40, -mov_box->get_height()/2, -10);
    message_bus->post_message(make_shared<Sprite_Update_Message>(mov_box));


}

void Collision_Detection_Test::handle_message(shared_ptr<Message> message)
{
    // Handle messages types this system cares about
    switch(message->get_id())
    {

        case ANIMATE:
        {
            logger->info("Animate message received.");

            mov_box->set_color(Color(0, 255, 0));

            // Move moving box based on space bar state
            if (space_pressed)
            {
                // Move right
                mov_box->move(1, 0, 0);
            }
            else
            {
                // Move left
                mov_box->move(-1, 0, 0);
            }
        }
        break;

        case KEY_UPDATE:
        {
            shared_ptr<Key_Update_Message> kum = dynamic_pointer_cast<Key_Update_Message>(message);
            logger->error("KEY: " + std::to_string(kum->get_key()));
            if (kum->get_key() == ' ')
                space_pressed = kum->is_pressed();
        }
        break;
    }
}
