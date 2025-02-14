#ifndef SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
#define SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_

#include <memory>
#include <vector>

#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/widgets/widget.hpp"

namespace taeto
{

namespace widgets
{

class Layout : public Widget
{
public:
    virtual ~Layout() {}

    virtual void add_widget(std::shared_ptr<taeto::widgets::Widget> widget, int stretch);

    DisplayPixelFrame render();

protected:
    std::vector<std::pair<std::shared_ptr<Widget>, int>> children_;
};

}   // namespace widgets

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
