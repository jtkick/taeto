#include "Test_Scene.h"

#include <memory>

#include "assets/lights/directional_light.h"
#include "assets/objects/zero.h"
#include "assets/objects/test_box.h"

namespace taeto
{

TestScene::TestScene()
{

}

TestScene::~TestScene()
{

}

void TestScene::load(int window_height, int window_width)
{
    // Load floor boxes
    for (int i = 0; i < 20; i++)
    {
        shared_ptr<TestBox> nt = make_shared<TestBox>(Color(255, 127, 0));
        nt->set_tags((nt->get_tags()) | FLOOR_TAG);
        nt->set_x_pixel_position(i * 16);
        message_bus->post_message(make_shared<SpriteUpdateMessage>(nt));
    }

    shared_ptr<TestBox> b2 = make_shared<TestBox>(Color(255, 127, 0));
    b2->set_tags((b2->get_tags()) | FLOOR_TAG);
    b2->set_x_pixel_position(64);
    b2->set_y_pixel_position(-9);
    message_bus->post_message(make_shared<SpriteUpdateMessage>(b2));

    // Load wall boxes
    shared_ptr<TestBox> b = make_shared<TestBox>(Color(0, 127, 255));
    b->set_tags((b->get_tags()) | WALL_TAG);
    b->set_x_pixel_position(64);
    b->set_y_pixel_position(-8);
    message_bus->post_message(make_shared<SpriteUpdateMessage>(b));



    // Add light
    Color c(255, 255, 255);
    Vector v(0, 0, 127);
    shared_ptr<DirectionalLight> dl = make_shared<DirectionalLight>(c, v);
    message_bus->post_message(make_shared<LightUpdateMessage>(dl));


    zero = make_shared<Zero>();
    message_bus->post_message(make_shared<SpriteUpdateMessage>(zero));
    // Attach Zero to message bus to get keystrokes
    message_bus->add_system(zero);

    auto pcm = make_shared<PlaceCameraMessage>(
        zero->get_x_pixel_position(),
        zero->get_y_pixel_position(),
        zero->get_z_pixel_position() + 10
    );
    message_bus->post_message(pcm);
}


void TestScene::handle_message(shared_ptr<Message> message)
{
    switch (message->get_id())
    {
        // Scene is about to be rendered, move camera before that happens
        case PRE_RENDER:
        {
            // Get camera offset
            int64_t x_offset = zero->get_x_speed() / 30000000000;

            // Update camera position
            auto pcm = make_shared<PlaceCameraMessage>(
                zero->get_x_pixel_position(),// + x_offset,
                -10,
                zero->get_z_pixel_position() + 10
            );
            message_bus->post_message(pcm);
        }
        break;
    }
}

}   // namespace taeto
