#include "OpeningIsland.h"paradigm

#include <memory>

#include "assets/objects/palm_tree.h"
#include "assets/objects/zero.h"
#include "messages/key_update_message.h"
#include "messages/place_camera_message.h"
#include "messages/sprite_update_message.h"

namespace taeto
{

OpeningIsland::OpeningIsland()
{

}

OpeningIsland::~OpeningIsland()
{

}

void OpeningIsland::load(int window_height, int window_width)
{
    shared_ptr<PalmTree> tree = make_shared<PalmTree>();
    message_bus->post_message(make_shared<SpriteUpdateMessage>(tree));

    zero = make_shared<Zero>();
    message_bus->post_message(make_shared<SpriteUpdateMessage>(zero));

    shared_ptr<PlaceCameraMessage> pcm = make_shared<PlaceCameraMessage>(
        zero->get_x_pixel_position(),
        zero->get_y_pixel_position(),
        zero->get_z_pixel_position() + 10
    );
}

void OpeningIsland::handle_message(shared_ptr<Message> message)
{
    switch (message->get_id())
    {
        case KEY_UPDATE:
        {
            shared_ptr<KeyUpdateMessage> kum =
                dynamic_pointer_cast<KeyUpdateMessage>(message);

            // Update camera position
            auto pcm = make_shared<PlaceCameraMessage>(
                zero->get_x_pixel_position(),
                zero->get_y_pixel_position(),
                zero->get_z_pixel_position() + 10
            );
        }
        break;
    }
}

}
