#include "NormalMappingTest.h"

#include <math.h>

#include <memory>

#include "assets/lights/point_light.h"
#include "assets/objects/normal_test.h"
#include "messages/message.h"

int const PI = 3.1415927;

namespace taeto
{

NormalMappingTest::NormalMappingTest()
{
    distance_ = 50;
    speed_ = 5.0;
    current_degree_ = 0.0;
    nt_ = make_shared<NormalTest>();
    pl_ = make_shared<PointLight>();

}

NormalMappingTest::~NormalMappingTest()
{

}

void NormalMappingTest::load(int window_height, int window_width)
{
    // Load normal box
    nt = make_shared<NormalTest>();
    nt->move(-16, -8, -10);
    message_bus->post_message(make_shared<SpriteUpdateMessage>(nt));

    // Load point light
    pl = make_shared<PointLight>(Color(255, 255, 255), 0.999);
    message_bus->post_message(make_shared<LightUpdateMessage>(pl));
}

void NormalMappingTest::handle_message(shared_ptr<Message> message)
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
            pl->place(x, y, -10);

            current_degree += speed;
            current_degree = fmod(current_degree, 360.0);
        }
        break;
    }
}

}   // namespace taeto
