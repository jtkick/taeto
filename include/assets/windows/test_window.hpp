#ifndef ASSETS_WINDOWS_TEST_WINDOW_HPP_
#define ASSETS_WINDOWS_TEST_WINDOW_HPP_

#include <glm/glm.hpp>

#include "systems/window_system/layout.hpp"
#include "systems/window_system/widget.hpp"

namespace taeto
{

class TestWindow : public Widget
{
    TestWindow();

    ~TestWindow();

    void size(glm::uvec2 v);

    DisplayPixelFrame render();

protected:
    HorizontalLayout hl_;
};

}   // namespace taeto

#endif  // ASSETS_WINDOWS_TEST_WINDOW_HPP_
