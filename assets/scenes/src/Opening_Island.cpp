#include "Opening_Island.h"

Opening_Island::Opening_Island()
{

}

Opening_Island::~Opening_Island()
{

}

void Opening_Island::load()
{
    shared_ptr<Palm_Tree> tree = make_shared<Palm_Tree>();
    message_bus->post_message(make_shared<Sprite_Update_Message>(tree));
}
