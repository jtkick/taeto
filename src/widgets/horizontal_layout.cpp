#include "taeto/widgets/horizontal_layout.hpp"

namespace taeto
{

void HorizontalLayout::size(glm::uvec2 v)
{
    size_ = v;

    int total_stretch = 0;
    for (auto& child : children_)
        total_stretch += child.second;

    int current_x = 0;
    for (auto& child : children_)
    {
        int stretch = child.second;
        int child_width;
        if (stretch > 0)
            child_width = (v.x * stretch) / total_stretch;
        else
            child_width = v.x / children_.size();
        child.first->position({current_x, 0});
        child.first->size({child_width, v.y});
        current_x += child_width;
    }
}

}   // namespace taeto