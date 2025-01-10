#include "systems/window_system/text_box.hpp"

#include "frames/display_pixel_frame.hpp"

namespace taeto
{

TextBox::TextBox()
{

}

TextBox::~TextBox()
{

}

void TextBox::text(DisplayPixelFrame& text)
{
    text_ = text;
}

DisplayPixelFrame& TextBox::render()
{
    return text_;
}

}   // namespace taeto