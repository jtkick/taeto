#ifndef ASSETS_SCENES_WINDOW_TEST_H_
#define ASSETS_SCENES_WINDOW_TEST_H_

#include <memory>

#include "assets/sprites/checkerboard.hpp"
#include "scenes/scene.hpp"
#include "systems/window_system/horizontal_layout.hpp"
#include "systems/window_system/widget.hpp"
#include "systems/window_system/text_box.hpp"

namespace taeto
{

class TestWindow : public Widget
{
    TestWindow();

    ~TestWindow();

    void size(glm::uvec2 v)
    {
        size_ = v;
        hl_.size(v - glm::uvec2(2, 2));
    };

    glm::uvec2 size()
    {
        return size_;
    }

    DisplayPixelFrame render()
    {
        DisplayPixelFrame result(size());
        
    };

protected:
    HorizontalLayout hl_;
};

class WindowTest : public taeto::Scene
{
public:
    WindowTest();

    ~WindowTest();

    void load();

private:
    std::shared_ptr<Checkerboard> cb_;
    std::shared_ptr<Widget> w_;
    std::shared_ptr<TextBox> tb_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_WINDOW_TEST_H_
