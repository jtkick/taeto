#ifndef ASSETS_OBJECTS_TEST_BOX_H_
#define ASSETS_OBJECTS_TEST_BOX_H_

#include <memory>

#include "components/color.h"
#include "components/sprite.h"

namespace taeto
{

class TestBox: public taeto::Sprite
{
public:
    TestBox(taeto::Color);

    void set_color(taeto::Color);

    void handle_collision(std::shared_ptr<taeto::Sprite>);
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_TEST_BOX_H_
