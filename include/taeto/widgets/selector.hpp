#ifndef WIDGETS_SELECTOR_HPP_
#define WIDGETS_SELECTOR_HPP_

#include <vector>

#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/widgets/widget.hpp"
#include "taeto/components/display_pixel.hpp"

namespace taeto
{

namespace widgets
{

class Selector : public taeto::Widget
{
public:
    Selector(
        std::vector<std::string> options,
        std::string brackets = "[]",
        int spacing = 2
    )   : options_(options),
          brackets_(brackets),
          spacing_(spacing)
    {
        selected_option_ = -1;
    };

    ~Selector() {};

    DisplayPixelFrame render();

    int selected() { return selected_option_; };
    void selected(int i) { selected_option_ = i; };

protected:
    std::vector<std::string> options_;
    std::string brackets_;
    int spacing_;
    int selected_option_;
};

}   // namespace widgets

}   // namespace taeto

#endif  // WIDGETS_SELECTOR_HPP_
