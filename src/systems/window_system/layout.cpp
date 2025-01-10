#include "systems/window_system/layout.hpp"

#include "systems/window_system/widget.hpp"

#include <memory>

namespace taeto
{

void Layout::add_widget(std::shared_ptr<Widget> widget, int stretch = 0)
{
    this->children_.push_back({widget, stretch});
}

DisplayPixelFrame Layout::render()
{
    DisplayPixelFrame result(this->size());
    for (auto& child : children_)
    {
        DisplayPixelFrame render = child.first->render();
        result.apply(
            render,
            child.first->position(),
            false,
            [](DisplayPixel& a, DisplayPixel& b)->DisplayPixel&
            {
                a.c = b.c;
                a.fg_color = taeto::mix_colors(a.fg_color, b.fg_color);
                a.bg_color = taeto::mix_colors(a.bg_color, b.bg_color);
                a.bold = b.bold;
                a.italic = b.italic;
                a.underline = b.underline;
                a.strikethrough = b.strikethrough;
                return a;
            }
        );
        return result;
    }
}

}   // namespace taeto
