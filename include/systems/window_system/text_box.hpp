#ifndef SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_
#define SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_

#include <memory>

#include "frames/display_pixel_frame.hpp"
#include "systems/window_system/widget.hpp"
#include "components/display_pixel.hpp"

namespace taeto
{

class TextBox : public Widget
{
public:
    TextBox();

    ~TextBox();

    void text(DisplayPixelFrame& text);

    // virtual void set_geometry(int y, int x, int height, int width) = 0;

    DisplayPixelFrame& render();

protected:
    DisplayPixelFrame text_;
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_TEXT_BOX_HPP_
