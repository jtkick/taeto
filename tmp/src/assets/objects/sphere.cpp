// #include "assets/object/sphere.hpp"
//
// #include <memory>
//
// #include "components/color.h"
// #include "components/frame.h"
// #include "components/sprite.h"
//
// namespace taeto
// {
//
// Sphere::Sphere(int diameter)
// {
//     height = (int)(diameter / 2.5);
//     width = diameter * 2;
//
//     x_position = 0;
//     y_position = 0;
//     z_position = 0;
//
//     current_frame = taeto::Frame(height, width);
//
//     int sphere_center_y = height / 2;
//     int sphere_center_x = width / 2;
//
//     int x_radius = diameter / 2;
//     int y_radius = (diameter / 2) / 2.5;
//
//     // Initialize pixels
//     for (int i = 0; i < height; ++i)
//     {
//         for (int j = 0; j < width; ++j)
//         {
//             taeto::Pixel& pixel = current_frame.get_pixel(i, j);
//             pixel.char = ' ';
//             pixel.foreground_color = taeto::Color(255, 255, 255);
//             pixel.background_color = taeto::Color(255, 255, 255);
//
//             // Calculate normal
//             int normal_z = (std::sqrt(i*i + j*j)
//             taeto::Vector v = taeto::Vector(
//                 x
//                 y
//                 z
//             );
//
//         }
//     }
//
//     current_frame.set_chars({r" _ ",
//                              r"(m)",
//                              r" = "});
//
//     taeto::Color w = taeto::Color(255, 255, 255);
//     taeto::Color g = taeto::Color(127, 127, 127);
//     taeto::Color a = taeto::Color(255, 0, 255, 0);
//
//     current_frame.set_foreground_colors({{w, w, w}, {w, w, w}, {g, g, g}});
//
//     current_frame.set_background_colors({{a, a, a}, {a, a, a}, {a, a, a}});
//
//     set_color(c);
//
//     // TODO: LOAD LIGHT DYNAMICALLY
//     light_ = std::make_shared<taeto::PointLight>(c);
//
//     respect_light_sources = false;
// }
//
// Sphere::set_color(taeto::Color c_)
// {
//     current_frame.get_pixel(1, 1).foreground_color = c_;
// }
//
//
// void Sphere::handle_collision(std::shared_ptr<taeto::Sprite> other_sprite)
// {
//
// }
//
// }   // namespace taeto
