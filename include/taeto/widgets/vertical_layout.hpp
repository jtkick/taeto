#ifndef SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_
#define SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_

#include "taeto/widgets/layout.hpp"

namespace taeto
{

namespace widgets
{

class VerticalLayout : public Layout
{
public:
    void size(glm::uvec2 v);
};

}   // namespace widgets

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_
