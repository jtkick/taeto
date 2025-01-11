#include "systems/window_system/text_box.hpp"

#include "components/display_pixel.hpp"
#include "frames/display_pixel_frame.hpp"

namespace taeto
{

DisplayPixelFrame TextBox::render()
{
    DisplayPixelFrame t(
        this->size(),
        DisplayPixel(' ', glm::vec4(1.0, 1.0, 1.0, 1.0),
                     glm::vec4(0.0, 0.0, 0.0, 0.0), false));
    for (int i = 0; i < size().x * size().y && i < text_.size(); i++)
        t.at({i%size().x, i/size().x}).c = text_.at(i);
    return t;
}

}   // namespace taeto