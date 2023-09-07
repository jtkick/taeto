#include "systems/render_system.hpp"

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/frame.h"
#include "components/position.hpp"

namespace taeto
{

RenderSystem::RenderSystem()
{

}

RenderSystem::RenderSystem(std::shared_ptr<spdlog::logger> l)
{
    logger_ = l;

    render_distance_ = 1000000000;
}

RenderSystem::~RenderSystem()
{

}

// TODO: ADD PRIORITY
bool comp(std::shared_ptr<Sprite> a, std::shared_ptr<Sprite> b) { return !(a->z_position <= b->z_position); }
//std::sort(sprites.begin(), sprites.end(), comp);

// WIP
// void RenderSystem::render_frame_by_drawing(
//     taeto::Frame &frame,
//     std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
//     std::vector<std::weak_ptr<taeto::Light>>& lights)
// {
//     // TODO: FIGURE OUT SKYBOXES IN THIS METHOD
//
//     // Initizlize counters
//     drawn_sprites_ = 0;
//
//     // Quick sanity check
//     if (camera.get_focal_length() < 1)
//     {
//         logger_->error("Drawing plane distance set to: " + std::to_string(camera.get_focal_length()));
//         return;
//     }
//
//     // Find all sprites that are going to be drawn
//     for (auto sprite_ptr = sprites.begin(); sprite_ptr != sprites.end(); sprite_ptr++)
//     {
//         // If beyond render distance, move on
//         if (camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position() > render_distance_ ||
//             (*sprite_ptr)->get_z_pixel_position() >= camera.get_z_pixel_position())
//         {
//             logger_->info("Sprite out of visible range, not rendering.");
//             (*sprite_ptr)->set_visible(false);
//             continue;
//         }
//
//         //                     ________
//         //                    | Object |
//         //     rendered       /¯¯¯¯¯¯¯¯
//         //      pixel        /|
//         //            \     / |
//         //             \   /  |
//         //              ┘ /   |
//         //---------------X---------------------  <- drawing_plane
//         //              /|    |
//         //             / |    | <------- camera.get_z_pixel_position() - current_sprite->get_z_pixel_position()
//         //            /  | <------------ camera.get_focal_length()
//         //           /   |    |
//         //         _/____|____|
//         //         \_/ ^    ^----- bounding_box_(left/right/top/bottom)
//         //         | | └---------- (x/y)
//         //          ¯
//         //          ^- camera
//         //
//
//         double z_diff = camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position();
//
//         //                                           -(frame.get_width() / 2) * z_diff
//         //  bounding_box_left = camera.get_x_pixel_position() + -----------------------------------
//         //                                                camera.get_focal_length()
//         long int bounding_box_left = camera.get_x_pixel_position() + (-((float)frame.get_width() / 2) * z_diff) / camera.get_focal_length();
//
//         //                                            (frame.get_width() + 1) / 2) * z_diff
//         //  bounding_box_right = camera.get_x_pixel_position() + ---------------------------------------
//         //                                                   camera.get_focal_length()
//         long int bounding_box_right = camera.get_x_pixel_position() + ((((float)frame.get_width() + 1) / 2) * z_diff) / camera.get_focal_length();
//
//         //                                          -(frame.get_height() / 2) * z_diff
//         //  bounding_box_top = camera.get_y_pixel_position() + ------------------------------------
//         //                                                camera.get_focal_length()
//         long int bounding_box_top = camera.get_y_pixel_position() + (-((float)frame.get_height() / 2) * z_diff) / camera.get_focal_length();
//
//         //                                            (frame.get_height() + 1) / 2) * z_diff
//         //  bounding_box_bottom = camera.get_y_pixel_position() + ---------------------------------------
//         //                                                   camera.get_focal_length()
//         long int bounding_box_bottom = camera.get_y_pixel_position() + ((((float)frame.get_height() + 1) / 2) * z_diff) / camera.get_focal_length();
//
//         // Mark sprite not visible if totally outside bounding box
//         if (((*sprite_ptr)->get_x_pixel_position() < bounding_box_left &&
//              (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() < bounding_box_left) ||
//             ((*sprite_ptr)->get_x_pixel_position() > bounding_box_right &&
//              (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() > bounding_box_right) ||
//             ((*sprite_ptr)->get_y_pixel_position() < bounding_box_top &&
//              (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() < bounding_box_top) ||
//             ((*sprite_ptr)->get_y_pixel_position() > bounding_box_bottom &&
//              (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() > bounding_box_bottom))
//         {
//             logger_->info("Sprite outside viewable area, not rendering.");
//             (*sprite_ptr)->set_visible(false);
//             continue;
//         }
//
//         // Sprite must be visible then
//         (*sprite_ptr)->set_visible(true);
//
//         // Keep track of how many sprites are being rendered
//         drawn_sprites++;
//
//         // Now that sprite is known to be at least partially visible, draw it on the frame
//
//         // First, map sprite location to pixel relative to camera
//         //                    (sprite_ptr->get_x_pixel_position() - camera.get_x_pixel_position()) * camera.get_focal_length()
//         //  drawn_left_pos = -----------------------------------------------------------------------------
//         //                                                 z_diff
//         long int drawn_left_pos = ((*sprite_ptr)->get_x_pixel_position() - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff;
//
//         //                     (sprite_ptr->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera.get_x_pixel_position()) * camera.get_focal_length()
//         //  drawn_right_pos = -------------------------------------------------------------------------------------------------------
//         //                                                                  z_diff
//         long int drawn_right_pos = ((*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff;
//
//         //                    (sprite_ptr->get_y_pixel_position() - camera.get_y_pixel_position()) * camera.get_focal_length()
//         //  drawn_top_pos = -----------------------------------------------------------------------------
//         //                                                 z_diff
//         long int drawn_top_pos = ((*sprite_ptr)->get_y_pixel_position() - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff;
//
//         //                     (sprite_ptr->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera.get_y_pixel_position()) * camera.get_focal_length()
//         //  drawn_bottom_pos = -------------------------------------------------------------------------------------------------------
//         //                                                                  z_diff
//         long int drawn_bottom_pos = ((*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff;
//
//         // Make values relative to top-left of frame rather than camera
//         //drawn_left_pos += frame.get_width() / 2;
//         //drawn_right_pos += frame.get_width() / 2;
//         //drawn_top_pos += frame.get_height() / 2;
//         //drawn_bottom_pos += frame.get_height() / 2;
//
//         // Keep boundaries from going off-frame
//         drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos);
//         drawn_right_pos = std::min<long unsigned int>(frame.get_width() - 1, drawn_right_pos);
//         drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
//         drawn_bottom_pos = std::min<long unsigned int>(frame.get_height() - 1, drawn_bottom_pos);
//
//         // Get ratio between z distances
//         double z_ratio = (float)(camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position()) / camera.get_focal_length();
//
//         for (int y = 0; y < (*sprite_ptr)->get_height(); y = (int)(y + z_ratio))
//         {
//             for (int x = 0; x < (*sprite_ptr)->get_width(); x = (int)(x + z_ratio))
//             {
//                 // Get pixel position relative to sprite
//                 long int sprite_y = (long int)(y + (*sprite_ptr)->get_y_pixel_position());
//                 long int sprite_x = (long int)(x + (*sprite_ptr)->get_x_pixel_position());
//
//                 // Get pixel of interest
//                 const taeto::Pixel& sprite_pixel = (*sprite_ptr)->get_pixel(sprite_y, sprite_x);
//
//                 // Map from relative to sprite to relative to camera
//                 long int frame_y = (long int)((sprite_y - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff);
//                 long int frame_x = (long int)((sprite_x - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff);
//
//                 // Map from relative to camera to relative to frame
//                 frame_y += frame.get_height() / 2;
//                 frame_x += frame.get_width() / 2;
//
//                 taeto::Pixel& frame_pixel = frame.get_pixel(frame_y, frame_x);
//
//                 frame_pixel.c = sprite_pixel.c;
//             }
//         }
//     }
//
//     // Update frame number
//     update_fps();
//
//     write_debug_info(frame);
// }




void RenderSystem::render_frame(
    taeto::Frame &rendered_frame,
    taeto::Camera &camera,
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
    std::vector<std::weak_ptr<taeto::Light>>& lights)
{
    // Get height and width for quick reference
    int h = rendered_frame.get_height();
    int w = rendered_frame.get_width();

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    ////////////////////////////////////////////////////////////////
    ////                      ALBEDO FRAME                      ////
    ////////////////////////////////////////////////////////////////

    // Loop over each 'pixel' in frame
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Vector for rendered pixels before they're combined into a single
            // displayed pixel
            static std::vector<std::tuple<taeto::Pixel, double>> pixel_stack =
                std::vector<std::tuple<taeto::Pixel, double>>();
            pixel_stack.clear();

            // TODO: MAKE SURE SPRITE AND LIGHT POINTERS AREN'T DEAD

            // Render each sprite at a time
            for (std::weak_ptr<Sprite> current_sprite_weak_ptr : sprites)
            {
                // Get pointer if not dead
                std::shared_ptr<taeto::Sprite> current_sprite;
                if (!(current_sprite = current_sprite_weak_ptr.lock()))
                    continue;

                // Get distance between sprite and camera
                double z_diff = camera.get_z_pixel_position() -
                                current_sprite->get_z_pixel_position();

                // Make sure sprite is at least in front of the camera and
                // within rendering distance
                // Also handle case where z-diff is 0 to prevent divide by zero error
                // if (z_diff <= 0 || z_diff > render_distance_)
                //     continue;

                // Get sprite pixel of interest depending on orientation plane
                // We're going to be very literal to keep things straight
                char plane_orientation =
                    current_sprite->get_plane_orientation();
                int dp_y = y - half_frame_height;
                int dp_x = x - half_frame_width;
                double sprite_z = 0.0;
                double sprite_y = 0.0;
                double sprite_x = 0.0;
                if (plane_orientation == 'Z')
                {
                    double z_diff = camera.get_z_pixel_position() -
                        current_sprite->get_z_pixel_position();
                    double sprite_y =
                        (((dp_y * z_diff) /
                          camera.get_focal_length()) +
                         camera.get_y_pixel_position()) -
                        current_sprite->get_y_pixel_position();
                    double sprite_x =
                        (((dp_x * z_diff) /
                          camera.get_focal_length()) +
                         camera.get_x_pixel_position()) -
                        current_sprite->get_x_pixel_position();
                }
                else if (plane_orientation == 'Y')
                {
                    double y_diff = camera.get_y_pixel_position() -
                        current_sprite->get_y_pixel_position();
                    double sprite_y =
                        (((dp_y * y_diff) /
                          camera.get_focal_length()) +
                         camera.get_z_pixel_position()) -
                        current_sprite->get_z_pixel_position();
                    double sprite_x =
                        (((dp_x * y_diff) /
                          camera.get_focal_length()) +
                         camera.get_x_pixel_position()) -
                        current_sprite->get_z_pixel_position();
                }

                // Map frame position to sprite plane position
                double abs_z = current_sprite->get_z_pixel_position();
                double abs_y = (((y - half_frame_height) * z_diff) / camera.get_focal_length()) + camera.get_y_pixel_position();
                double abs_x = (((x - half_frame_width) * z_diff) / camera.get_focal_length()) + camera.get_x_pixel_position();

                // Get distance to camera
                double distance_to_camera =
                    std::sqrt(abs_z * abs_z + abs_y * abs_y + abs_x * abs_x);

                // Map to relative to sprite origin
                double rel_y = abs_y - current_sprite->get_y_pixel_position();
                double rel_x = abs_x - current_sprite->get_x_pixel_position();

                // If pixel doesn't overlap with sprite, move on to next pixel
                if (sprite_x < 0 || sprite_x >= current_sprite->get_width() ||
                    sprite_y < 0 || sprite_y >= current_sprite->get_height())
                     continue;

                // Get pixel of interest
                taeto::Pixel current_pixel =
                    current_sprite->get_pixel(sprite_y, sprite_x);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be drawn
                if (current_pixel.foreground_color.alpha == 0)
                    continue;

                // Compute lighting for this pixel
                taeto::Color received_light(0, 0, 0);
                for (std::weak_ptr<Light> light_weak_ptr : lights)
                {
                    // Get pointer if not dead
                    std::shared_ptr<taeto::Light> light;
                    if (!(light = light_weak_ptr.lock()))
                        continue;

                    // Light color at this pixel location
                    taeto::Color light_color = light->get_color(abs_x, abs_y, abs_z);

                    // Get light vector and pixel normal
                    const taeto::Vector &pixel_normal = current_pixel.normal;
                    const taeto::Vector light_vector = light->get_vector(abs_x, abs_y, abs_z);

                    // TODO: PUT THIS IN A VECTOR OPERATOR METHOD
                    // Get vector components
                    char x1 = pixel_normal.get_x_component();
                    char y1 = pixel_normal.get_y_component();
                    char z1 = pixel_normal.get_z_component();
                    char x2 = light_vector.get_x_component();
                    char y2 = light_vector.get_y_component();
                    char z2 = light_vector.get_z_component();

                    // Calculate angle between the two
                    float angle = acos((x1 * x2 + y1 * y2 + z1 * z2) /
                                       (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) *
                                        sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2))));

                    // Scale from 0 to pi, to between 0 and 255
                    unsigned char brightness = 255 - (unsigned char)(angle * 81.1690378636);

                    // Adjust light brightness accordingly
                    light_color.set_brightness(brightness);

                    // Add light to accumulated pixel light
                    received_light += light_color;
                }

                // Apply light to pixel
                current_pixel.foreground_color = current_pixel.foreground_color * received_light;
                current_pixel.background_color = current_pixel.background_color * received_light;

                // Add pixel to stack for combining into rendered pixel
                pixel_stack.push_back({current_pixel, distance_to_camera});

                // If this sprite's pixel is fully opaque, we're done rendering this pixel
                if (current_pixel.background_color.alpha == 255)
                    break;
            }

            // Add skybox pixel to stack
            // TODO: SKYBOXES
            // taeto::Pixel skybox_pixel = taeto::Pixel(' ', taeto::Color(255, 255, 255, 255), taeto::Color(0, 0, 0, 255), false);
            // pixel_stack.push_back(skybox_pixel);

            if (pixel_stack.size() == 0)
            {
                rendered_frame.get_pixel(y, x).clear();
                continue;
            }



            // I SAY "FUCK IT"

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel(y, x) = std::get<0>(pixel_stack.at(0));
            continue;





            // Now that we have all the rendered pixels, combine them together
            taeto::Pixel rendered_pixel =
                std::get<0>(pixel_stack.at(pixel_stack.size() - 1));
            for (int i = pixel_stack.size() - 2; i >= 0; --i)
            {
                // Get new background color
                taeto::Color bg = rendered_pixel.background_color &
                    std::get<0>(pixel_stack.at(i)).background_color;
                rendered_pixel = std::get<0>(pixel_stack.at(i));
                rendered_pixel.background_color = bg;
            }

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel(y, x) = rendered_pixel;
        }
    }

    ////////////////////////////////////////////////////////////////
    ////                     LIGHTING PASS                      ////
    ////////////////////////////////////////////////////////////////



}

}   // namespace taeto
