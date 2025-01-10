#ifndef SYSTEMS_WINDOW_SYSTEM_WIDGET_HPP_
#define SYSTEMS_WINDOW_SYSTEM_WIDGET_HPP_

#include <string>

#include <glm/glm.hpp>

#include "frames/display_pixel_frame.hpp"

namespace taeto
{

class Widget
{
public:

    Widget();

    Widget(std::string);

    ~Widget();

    /**
     * Get the name of this object.
     */
    std::string name();

    /**
     * Set the name of this object.
     */
    void name(std::string);

    /**
     * Set the shape and position of the widget.
     */
    // void geometry(int, int, int, int);

    glm::ivec2 position();
    void position(glm::ivec2);

    glm::uvec2 size();
    void size(glm::uvec2);

    virtual DisplayPixelFrame render();

protected:
    /**
     * Name of this object.
     */
    std::string name_;

    /**
     * Widget dimensions.
     */
    glm::vec2 position_;
    glm::uvec2 size_;
};

}   // namespace taeto

#endif  // SYSTEMS_WINDOW_SYSTEM_WIDGET_HPP_
