#ifndef SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_
#define SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_

#include "taeto/widgets/layout.hpp"

namespace taeto
{

class VerticalLayout : public Layout
{
public:
    void size(glm::uvec2 v);
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_VERTICAL_LAYOUT_HPP_
