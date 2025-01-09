#ifndef SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
#define SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_

#include "systems/window_system/widget.hpp"

#include <memory>
#include <vector>

namespace taeto
{

class Layout
{
public:
    virtual ~Layout() {}

    virtual void add_widget(std::shared_ptr<Widget> widget, int stretch);

    virtual void set_geometry(int y, int x, int height, int width) = 0;

    virtual void render();

protected:
    std::vector<std::pair<std::shared_ptr<Widget>, int>> children_;
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_LAYOUT_HPP_
