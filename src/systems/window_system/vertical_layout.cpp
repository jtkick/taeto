#include "systems/window_system/vertical_layout.hpp"

namespace taeto
{

void VerticalLayout::size(glm::uvec2 v)
{
    int total_stretch = 0;
    for (auto& child : children_)
        total_stretch += child.second;

    int current_y = 0;
    for (auto& child : children_)
    {
        int stretch = child.second;
        int child_height;
        if (stretch > 0)
            child_height = (v.y * stretch) / total_stretch;
        else
            child_height = v.y / children_.size();
        child.first->position({this->position().x, current_y});
        child.first->size({v.x, child_height});
        current_y += child_height;
    }
}

}   // namespace taeto