#ifndef ASSETS_OBJECTS_ZERO_H_
#define ASSETS_OBJECTS_ZERO_H_

#include <memory>

#include "components/sprite.h"
#include "message_layer/Message.h"
#include "message_layer/Message_Bus_Entry.h"

uint64_t const FLOOR_TAG = 0x0000000000000001;
uint64_t const WALL_TAG = 0x0000000000000002;
std::chrono::milliseconds const DEFAULT_JUMP_TIME(400);

namespace taeto
{

class Zero: public Message_Bus_Entry, public Sprite
{
public:
    Zero();

    void handle_collision(std::shared_ptr<taeto::Sprite>);

    void handle_message(std::shared_ptr<taeto::Message>);

    void add_collide_object(std::shared_ptr<taeto::Sprite>);

private:
    std::vector<std::shared_ptr<taeto::Sprite>> collide_objects_;

    // Keys pressed
    bool space_ = false;
    bool w_ = false;
    bool a_ = false;
    bool s_ = false;
    bool d_ = false;

    // Last time animate() was run
    std::chrono::milliseconds last_animate_call_;

    // Timer for how long to push Zero up after jump pressed
    std::chrono::milliseconds jump_timer_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_ZERO_H_
