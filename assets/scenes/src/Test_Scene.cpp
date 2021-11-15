#include "Test_Scene.h"

Test_Scene::Test_Scene()
{

}

Test_Scene::~Test_Scene()
{

}

void Test_Scene::load(int window_height, int window_width)
{
    // Load floor boxes
    for (int i = 0; i < 3; i++)
    {
        shared_ptr<Normal_Test> nt = make_shared<Normal_Test>();
        nt->set_tags((nt->get_tags()) | FLOOR);
        nt->set_x_pixel_position(i * 32);
        message_bus->post_message(make_shared<Sprite_Update_Message>(nt));
    }

    // Add light
    Color c(200, 200, 255);
    Vector v(0, 0, 127);
    shared_ptr<Directional_Light> dl = make_shared<Directional_Light>(c, v);
    message_bus->post_message(make_shared<Light_Update_Message>(dl));


    zero = make_shared<Zero>();
    message_bus->post_message(make_shared<Sprite_Update_Message>(zero));

    auto pcm = make_shared<Place_Camera_Message>(zero->get_x_pixel_position(),
                                                 zero->get_y_pixel_position(),
                                                 zero->get_z_pixel_position() + 10);
    message_bus->post_message(pcm);


}

void Test_Scene::handle_message(shared_ptr<Message> message)
{
    switch (message->get_id())
    {
        case ANIMATE:
        {
            if (w)
            {
                zero->move(0, -1, 0);
            }
            if (a)
            {
                zero->move(-1, 0, 0);
            }
            if (s)
            {
                zero->move(0, 1, 0);
            }
            if (d)
            {
                zero->move(1, 0, 0);
            }

            // Update camera position
            logger->info("POSTING PLACE CAMERA MESAAGE");
            auto pcm = make_shared<Place_Camera_Message>(zero->get_x_pixel_position(),
                                                         zero->get_y_pixel_position(),
                                                         zero->get_z_pixel_position() + 10);
            message_bus->post_message(pcm);
        }
        break;

        case KEY_UPDATE:
        {
            logger->info("TEST SCENE RECEIVED KEY UPDATE");

            shared_ptr<Key_Update_Message> kum = dynamic_pointer_cast<Key_Update_Message>(message);

            // Move camera based on key
            switch(kum->get_key())
            {
                case 'w':
                    w = kum->is_pressed();
                break;

                case 'a':
                    a = kum->is_pressed();
                break;

                case 's':
                    s = kum->is_pressed();
                break;

                case 'd':
                    d = kum->is_pressed();
                break;
            }
        }
        break;
    }
}
