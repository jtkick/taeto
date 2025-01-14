#ifndef SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_
#define SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_

#include <memory>

#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/widgets/widget.hpp"
#include "taeto/components/display_pixel.hpp"

namespace taeto
{

class TextBox : public Widget
{
public:
    TextBox(std::string s) { text_ = s; };

    ~TextBox() {};

    DisplayPixelFrame render();

protected:
    std::string text_;
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_
