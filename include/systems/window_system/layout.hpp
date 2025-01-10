#ifndef SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
#define SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_

#include <memory>
#include <vector>

#include "frames/display_pixel_frame.hpp"
#include "systems/window_system/widget.hpp"

namespace taeto
{

class Layout : public Widget
{
public:
    virtual ~Layout() {}

    virtual void add_widget(std::shared_ptr<Widget> widget, int stretch);

    DisplayPixelFrame render();

protected:
    std::vector<std::pair<std::shared_ptr<Widget>, int>> children_;
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
