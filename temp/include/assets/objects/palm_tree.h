#ifndef ASSETS_OBJECTS_PALM_TREE_H_
#define ASSETS_OBJECTS_PALM_TREE_H_

#include <memory>

#include "components/frame.h"
#include "components/sprite.h"

namespace taeto
{

class PalmTree: public Sprite
{
public:
    PalmTree();

    std::shared_ptr<taeto::Frame> get_current_frame();

private:
    taeto::Frame default_frame_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_PALM_TREE_H_
