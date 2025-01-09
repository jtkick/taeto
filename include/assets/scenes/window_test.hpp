#ifndef ASSETS_SCENES_WINDOW_TEST_H_
#define ASSETS_SCENES_WINDOW_TEST_H_

#include <memory>

#include "assets/sprites/checkerboard.hpp"
#include "scenes/scene.hpp"
#include "systems/window_system/widget.hpp"

namespace taeto
{

class WindowTest : public taeto::Scene
{
public:
    WindowTest();

    ~WindowTest();

    void load();

private:
    std::shared_ptr<Checkerboard> cb_;
    std::shared_ptr<Widget> w_;
};

}   // namespace taeto

#endif  // ASSETS_SCENES_WINDOW_TEST_H_
