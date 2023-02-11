#ifndef ASSETS_SCENES_OPENING_ISLAND_H_
#define ASSETS_SCENES_OPENING_ISLAND_H_

#include <memory>

#include "assets/objects/zero.h"
#include "message_layer/Message.h"
#include "scenes/scene.h"

namespace taeto
{

class OpeningIsland : public Scene
{
public:
    OpeningIsland();

    ~OpeningIsland();

    void handle_message(shared_ptr<Message>);

    void load(int, int);

private:
    shared_ptr<Zero> zero;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_OPENING_ISLAND_H_
