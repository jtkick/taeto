#include "Opening_Island.h"

Opening_Island::Opening_Island(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

    shared_ptr<Palm_Tree> tree = make_shared<Palm_Tree>();
    message_bus->post_message(make_shared<Sprite_Update_Message>(tree));
}

Opening_Island::~Opening_Island()
{

}
