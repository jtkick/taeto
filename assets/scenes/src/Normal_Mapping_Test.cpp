#include "Normal_Mapping_Test.h"

Normal_Mapping_Test::Normal_Mapping_Test()
{

}

Normal_Mapping_Test::~Normal_Mapping_Test()
{

}

void Normal_Mapping_Test::load(int window_height, int window_width)
{
    // Load normal box
    nt = make_shared<Normal_Test>();
    nt->move(-16, -8, -10);
    message_bus->post_message(make_shared<Sprite_Update_Message>(nt));

    // Load point light
    pl = make_shared<Point_Light>(Color(255, 255, 255), 0.999);
    message_bus->post_message(make_shared<Light_Update_Message>(pl));
}

void Normal_Mapping_Test::handle_message(shared_ptr<Message> message)
{
    // Handle messages types this system cares about
    switch(message->get_id())
    {

        case ANIMATE:
        {
            logger->info("Animate message received.");

            // Move light in a circle about the box
            long int x = distance * cos(current_degree * PI / 180);
            long int y = distance * sin(current_degree * PI / 180);

            logger->info("x: " + std::to_string(x));
            logger->info("y: " + std::to_string(y));

            pl->place(x, y, -10);

            current_degree += speed;
            current_degree = fmod(current_degree, 360.0);
        }
        break;
    }
}
