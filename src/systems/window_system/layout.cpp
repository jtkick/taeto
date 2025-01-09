#include "systems/window_system/layout.hpp"

#include "systems/window_system/widget.hpp"

#include <memory>

namespace taeto
{

void Layout::add_widget(std::shared_ptr<Widget> widget, int stretch = 0)
{
    this->children_.push_back({widget, stretch});
}

void Layout::render()
{
    for (auto& child : this->children_)
    {
        child.first->render();
    }
}

}   // namespace taeto
