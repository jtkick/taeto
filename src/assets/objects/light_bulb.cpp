#include "assets/object/light_bulb.hpp"

#include <memory>

#include "components/color.h"
#include "components/frame.h"
#include "components/sprite.h"

namespace taeto
{

LightBulb::LightBulb(taeto::Color c)
{
    height = 3;
    width = 3;

    x_position = 0;
    y_position = 0;
    z_position = 0;

    current_frame = taeto::Frame(height, width);

    current_frame.set_chars({r" _ ",
                             r"(m)",
                             r" = "});

    taeto::Color w = taeto::Color(255, 255, 255);
    taeto::Color g = taeto::Color(127, 127, 127);
    taeto::Color a = taeto::Color(255, 0, 255, 0);

    current_frame.set_foreground_colors({{w, w, w}, {w, w, w}, {g, g, g}});

    current_frame.set_background_colors({{a, a, a}, {a, a, a}, {a, a, a}});

    set_color(c);

    // TODO: LOAD LIGHT DYNAMICALLY
    light_ = std::make_shared<taeto::PointLight>(c);

    respect_light_sources = false;
}

LightBulb::set_color(taeto::Color c_)
{
    current_frame.get_pixel(1, 1).foreground_color = c_;
}


void LightBulb::handle_collision(std::shared_ptr<taeto::Sprite> other_sprite)
{

}

}   // namespace taeto
