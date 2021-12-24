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
    for (int i = 0; i < 20; i++)
    {
        shared_ptr<Test_Box> nt = make_shared<Test_Box>(Color(255, 127, 0));
        nt->set_tags((nt->get_tags()) | FLOOR_TAG);
        nt->set_x_pixel_position(i * 16);
        message_bus->post_message(make_shared<Sprite_Update_Message>(nt));
    }

    shared_ptr<Test_Box> b2 = make_shared<Test_Box>(Color(255, 127, 0));
    b2->set_tags((b2->get_tags()) | FLOOR_TAG);
    b2->set_x_pixel_position(64);
    b2->set_y_pixel_position(-9);
    message_bus->post_message(make_shared<Sprite_Update_Message>(b2));

    // Load wall boxes
    shared_ptr<Test_Box> b = make_shared<Test_Box>(Color(0, 127, 255));
    b->set_tags((b->get_tags()) | WALL_TAG);
    b->set_x_pixel_position(64);
    b->set_y_pixel_position(-8);
    message_bus->post_message(make_shared<Sprite_Update_Message>(b));



    // Add light
    Color c(255, 255, 255);
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
                //zero->move(-1, 0, 0);
                zero->set_x_speed(zero->get_x_speed() + -30000000000.0);
                //zero->set_x_force(-500000000000.0);
            }
            if (s)
            {
                zero->move(0, 1, 0);
            }
            if (d)
            {
                //zero->move(1, 0, 0);
                zero->set_x_speed(zero->get_x_speed() + 30000000000.0);
                //zero->set_x_force(500000000000.0);
            }

            // Cap Zero's speed
            zero->set_x_speed(zero->get_x_speed() * 0.9);

            // Update which direction Zero is facing
            if (a && !d)
            {
                zero->set_current_frame("backward");
            }
            else if (!a && d)
            {
                zero->set_current_frame("forward");
            }
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

                // Use 'q' to reset Zero's position
                case 'q':
                    if (kum->is_pressed());
                    {
                        zero->set_x_pixel_position(0);
                        zero->set_y_pixel_position(-10);
                    }
                break;

            }
        }
        break;

        // Scene is about to be rendered, move camera before that happens
        case PRE_RENDER:
        {
            // Get camera offsets
            int64_t x_offset = zero->get_x_speed() / 30000000000;
            int64_t y_position = zero->get_y_pixel_position() - 5;

            // Update camera position
            logger->info("POSTING PLACE CAMERA MESAAGE");
            auto pcm = make_shared<Place_Camera_Message>(zero->get_x_pixel_position() + x_offset,
                                                         y_position,
                                                         zero->get_z_pixel_position() + 10);
            message_bus->post_message(pcm);
        }
        break;
    }
}
