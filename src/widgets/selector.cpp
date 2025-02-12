#include "taeto/widgets/selector.hpp"

#include "taeto/components/display_pixel.hpp"
#include "taeto/frames/display_pixel_frame.hpp"

namespace taeto
{

namespace widgets
{

DisplayPixelFrame Selector::render()
{
    DisplayPixel d('X', glm::vec4(1.0), glm::vec4(0.0), false);

    DisplayPixelFrame t(this->size(), d);

    int button_width = (this->size().x - (spacing_ * (options_.size() + 1))) / options_.size();
    int current_x = 0;

    // Add space at beginning of line
    for (int i = 0; i < spacing_; ++i)
        t.at({current_x++, 0}).c = ' ';

    for (int i = 0; i < options_.size(); ++i)
    {
        // Calculate space on either side of the option, between brackets
        int spaces = button_width - 2 - options_.at(i).size();
        int left_padding = spaces / 2;
        int right_padding = spaces - left_padding;

        // Check if option should be highlighted
        if (i == selected_option_)
            d = DisplayPixel('X', glm::vec4(0.0), glm::vec4(1.0), false);

        // Add the current option to the entire widget
        t.at({current_x++, 0}).c = brackets_.at(0);
        for (int j = 0; j < left_padding; ++j)
            t.at({current_x++, 0}).c = ' ';
        for (int j = 0; j < options_.at(i).size(); ++j)
            t.at({current_x++, 0}).c = options_.at(i).at(j);
        for (int j = 0; j < right_padding; ++j)
            t.at({current_x++, 0}).c = ' ';
        t.at({current_x++, 0}).c = brackets_.at(1);

        // Reset colors
        d = DisplayPixel('X', glm::vec4(1.0), glm::vec4(0.0), false);

        // Add more spacing
        for (int i = 0; i < spacing_; ++i)
            t.at({current_x++, 0}).c = ' ';
    }

    return t;
}

}   // namespace widgets

}   // namespace taeto