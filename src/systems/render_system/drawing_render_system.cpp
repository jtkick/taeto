#include "systems/render_system/drawing_render_system.hpp"

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/camera.hpp"
#include "frames/display_pixel_frame.hpp"
#include "object/light.hpp"
#include "object/sprite.hpp"
// #include "components/position.hpp"

namespace taeto
{

void DrawingRenderSystem::render_frame(
    taeto::DisplayPixelFrame &rendered_frame,
    taeto::Camera &camera,
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
    std::vector<std::weak_ptr<taeto::Light>>& lights)
{
    // TODO: FIGURE OUT SKYBOXES IN THIS METHOD

    // // Initizlize counters
    // drawn_sprites_ = 0;
    //
    // // Quick sanity check
    // if (camera.get_focal_length() < 1)
    // {
    //     logger_->error("Drawing plane distance set to: " + std::to_string(camera.get_focal_length()));
    //     return;
    // }
    //
    // // Find all sprites that are going to be drawn
    // for (auto sprite_ptr = sprites.begin(); sprite_ptr != sprites.end(); sprite_ptr++)
    // {
    //     // If beyond render distance, move on
    //     if (camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position() > render_distance_ ||
    //         (*sprite_ptr)->get_z_pixel_position() >= camera.get_z_pixel_position())
    //     {
    //         logger_->info("Sprite out of visible range, not rendering.");
    //         (*sprite_ptr)->set_visible(false);
    //         continue;
    //     }
    //
    //     //                     ________
    //     //                    | Object |
    //     //     rendered       /¯¯¯¯¯¯¯¯
    //     //      pixel        /|
    //     //            \     / |
    //     //             \   /  |
    //     //              ┘ /   |
    //     //---------------X---------------------  <- drawing_plane
    //     //              /|    |
    //     //             / |    | <------- camera.get_z_pixel_position() - current_sprite->get_z_pixel_position()
    //     //            /  | <------------ camera.get_focal_length()
    //     //           /   |    |
    //     //         _/____|____|
    //     //         \_/ ^    ^----- bounding_box_(left/right/top/bottom)
    //     //         | | └---------- (x/y)
    //     //          ¯
    //     //          ^- camera
    //     //
    //
    //     double z_diff = camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position();
    //
    //     //                                           -(frame.get_width() / 2) * z_diff
    //     //  bounding_box_left = camera.get_x_pixel_position() + -----------------------------------
    //     //                                                camera.get_focal_length()
    //     long int bounding_box_left = camera.get_x_pixel_position() + (-((float)frame.get_width() / 2) * z_diff) / camera.get_focal_length();
    //
    //     //                                            (frame.get_width() + 1) / 2) * z_diff
    //     //  bounding_box_right = camera.get_x_pixel_position() + ---------------------------------------
    //     //                                                   camera.get_focal_length()
    //     long int bounding_box_right = camera.get_x_pixel_position() + ((((float)frame.get_width() + 1) / 2) * z_diff) / camera.get_focal_length();
    //
    //     //                                          -(frame.get_height() / 2) * z_diff
    //     //  bounding_box_top = camera.get_y_pixel_position() + ------------------------------------
    //     //                                                camera.get_focal_length()
    //     long int bounding_box_top = camera.get_y_pixel_position() + (-((float)frame.get_height() / 2) * z_diff) / camera.get_focal_length();
    //
    //     //                                            (frame.get_height() + 1) / 2) * z_diff
    //     //  bounding_box_bottom = camera.get_y_pixel_position() + ---------------------------------------
    //     //                                                   camera.get_focal_length()
    //     long int bounding_box_bottom = camera.get_y_pixel_position() + ((((float)frame.get_height() + 1) / 2) * z_diff) / camera.get_focal_length();
    //
    //     // Mark sprite not visible if totally outside bounding box
    //     if (((*sprite_ptr)->get_x_pixel_position() < bounding_box_left &&
    //          (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->width() < bounding_box_left) ||
    //         ((*sprite_ptr)->get_x_pixel_position() > bounding_box_right &&
    //          (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->width() > bounding_box_right) ||
    //         ((*sprite_ptr)->get_y_pixel_position() < bounding_box_top &&
    //          (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->height() < bounding_box_top) ||
    //         ((*sprite_ptr)->get_y_pixel_position() > bounding_box_bottom &&
    //          (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->height() > bounding_box_bottom))
    //     {
    //         logger_->info("Sprite outside viewable area, not rendering.");
    //         (*sprite_ptr)->visible(false);
    //         continue;
    //     }
    //
    //     // Sprite must be visible then
    //     (*sprite_ptr)->visible(true);
    //
    //     // Keep track of how many sprites are being rendered
    //     drawn_sprites++;
    //
    //     // Now that sprite is known to be at least partially visible, draw it on the frame
    //
    //     // First, map sprite location to pixel relative to camera
    //     //                    (sprite_ptr->get_x_pixel_position() - camera.get_x_pixel_position()) * camera.get_focal_length()
    //     //  drawn_left_pos = -----------------------------------------------------------------------------
    //     //                                                 z_diff
    //     long int drawn_left_pos = ((*sprite_ptr)->get_x_pixel_position() - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff;
    //
    //     //                     (sprite_ptr->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera.get_x_pixel_position()) * camera.get_focal_length()
    //     //  drawn_right_pos = -------------------------------------------------------------------------------------------------------
    //     //                                                                  z_diff
    //     long int drawn_right_pos = ((*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->width() - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff;
    //
    //     //                    (sprite_ptr->get_y_pixel_position() - camera.get_y_pixel_position()) * camera.get_focal_length()
    //     //  drawn_top_pos = -----------------------------------------------------------------------------
    //     //                                                 z_diff
    //     long int drawn_top_pos = ((*sprite_ptr)->get_y_pixel_position() - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff;
    //
    //     //                     (sprite_ptr->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera.get_y_pixel_position()) * camera.get_focal_length()
    //     //  drawn_bottom_pos = -------------------------------------------------------------------------------------------------------
    //     //                                                                  z_diff
    //     long int drawn_bottom_pos = ((*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->height() - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff;
    //
    //     // Make values relative to top-left of frame rather than camera
    //     //drawn_left_pos += frame.get_width() / 2;
    //     //drawn_right_pos += frame.get_width() / 2;
    //     //drawn_top_pos += frame.get_height() / 2;
    //     //drawn_bottom_pos += frame.get_height() / 2;
    //
    //     // Keep boundaries from going off-frame
    //     drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos);
    //     drawn_right_pos = std::min<long unsigned int>(frame.width() - 1, drawn_right_pos);
    //     drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
    //     drawn_bottom_pos = std::min<long unsigned int>(frame.height() - 1, drawn_bottom_pos);
    //
    //     // Get ratio between z distances
    //     double z_ratio = (float)(camera.get_z_pixel_position() - (*sprite_ptr)->get_z_pixel_position()) / camera.get_focal_length();
    //
    //     for (int y = 0; y < (*sprite_ptr)->height(); y = (int)(y + z_ratio))
    //     {
    //         for (int x = 0; x < (*sprite_ptr)->width(); x = (int)(x + z_ratio))
    //         {
    //             // Get pixel position relative to sprite
    //             long int sprite_y = (long int)(y + (*sprite_ptr)->get_y_pixel_position());
    //             long int sprite_x = (long int)(x + (*sprite_ptr)->get_x_pixel_position());
    //
    //             // Get pixel of interest
    //             const taeto::Pixel& sprite_pixel = (*sprite_ptr)->get_pixel(sprite_y, sprite_x);
    //
    //             // Map from relative to sprite to relative to camera
    //             long int frame_y = (long int)((sprite_y - camera.get_y_pixel_position()) * camera.get_focal_length() / z_diff);
    //             long int frame_x = (long int)((sprite_x - camera.get_x_pixel_position()) * camera.get_focal_length() / z_diff);
    //
    //             // Map from relative to camera to relative to frame
    //             frame_y += frame.height() / 2;
    //             frame_x += frame.width() / 2;
    //
    //             taeto::Pixel& frame_pixel = frame.get_pixel_at(frame_y, frame_x);
    //
    //             frame_pixel.c = sprite_pixel.c;
    //         }
    //     }
    // }
}

}   // namespace taeto
