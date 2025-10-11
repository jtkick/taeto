#ifndef OBJECTS_IWIDGET_HPP_
#define OBJECTS_IWIDGET_HPP_

#include <string>

#include <glm/glm.hpp>

#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/objects/isprite.hpp"

namespace taeto
{

class IWidget : public ISprite
{
public:
    void child(std::shared_ptr<IWidget> child) { child_ = child; };
    std::shared_ptr<IWidget> child() { return child_; };

protected:
    std::shared_ptr<IWidget> child_;
};

}   // namespace taeto

#endif  // OBJECTS_IWIDGET_HPP_
