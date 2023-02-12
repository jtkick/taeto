#include "systems/render_system.hpp"

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/frame.h"

namespace taeto
{

RenderSystem::RenderSystem()
{

}

RenderSystem::RenderSystem(std::shared_ptr<spdlog::logger> l)
{
    logger_ = l;

    camera_x_position_ = 0;
    camera_y_position_ = 0;
    camera_z_position_ = 0;

    // Drawing plane distance can never be lower than 1
    focal_length_ = 10;

    frame_number_ = 0;

    render_distance_ = 1000000000;
}

RenderSystem::~RenderSystem()
{

}

// TODO: ADD PRIORITY
bool comp(std::shared_ptr<Sprite> a, std::shared_ptr<Sprite> b) { return !(a->z_position <= b->z_position); }
//std::sort(sprites.begin(), sprites.end(), comp);

// WIP
void RenderSystem::render_frame_by_drawing(taeto::Frame &frame)
{
    // TODO: FIGURE OUT SKYBOXES IN THIS METHOD

    // Initizlize counters
    drawn_sprites_ = 0;

    // Quick sanity check
    if (focal_length_ < 1)
    {
        logger_->error("Drawing plane distance set to: " + std::to_string(focal_length_));
        return;
    }

    // Find all sprites that are going to be drawn
    for (auto sprite_ptr = sprites_.begin(); sprite_ptr != sprites_.end(); sprite_ptr++)
    {
        // If beyond render distance, move on
        if (camera_z_position_ - (*sprite_ptr)->get_z_pixel_position() > render_distance_ ||
            (*sprite_ptr)->get_z_pixel_position() >= camera_z_position_)
        {
            logger_->info("Sprite out of visible range, not rendering.");
            (*sprite_ptr)->set_visible(false);
            continue;
        }

        //                     ________
        //                    | Object |
        //     rendered       /¯¯¯¯¯¯¯¯
        //      pixel        /|
        //            \     / |
        //             \   /  |
        //              ┘ /   |
        //---------------X---------------------  <- drawing_plane
        //              /|    |
        //             / |    | <------- camera_z_position_ - current_sprite->get_z_pixel_position()
        //            /  | <------------ focal_length_
        //           /   |    |
        //         _/____|____|
        //         \_/ ^    ^----- bounding_box_(left/right/top/bottom)
        //         | | └---------- (x/y)
        //          ¯
        //          ^- camera
        //

        double z_diff = camera_z_position_ - (*sprite_ptr)->get_z_pixel_position();

        //                                           -(frame.get_width() / 2) * z_diff
        //  bounding_box_left = camera_x_position_ + -----------------------------------
        //                                                focal_length_
        long int bounding_box_left = camera_x_position_ + (-((float)frame.get_width() / 2) * z_diff) / focal_length_;

        //                                            (frame.get_width() + 1) / 2) * z_diff
        //  bounding_box_right = camera_x_position_ + ---------------------------------------
        //                                                   focal_length_
        long int bounding_box_right = camera_x_position_ + ((((float)frame.get_width() + 1) / 2) * z_diff) / focal_length_;

        //                                          -(frame.get_height() / 2) * z_diff
        //  bounding_box_top = camera_y_position_ + ------------------------------------
        //                                                focal_length_
        long int bounding_box_top = camera_y_position_ + (-((float)frame.get_height() / 2) * z_diff) / focal_length_;

        //                                            (frame.get_height() + 1) / 2) * z_diff
        //  bounding_box_bottom = camera_y_position_ + ---------------------------------------
        //                                                   focal_length_
        long int bounding_box_bottom = camera_y_position_ + ((((float)frame.get_height() + 1) / 2) * z_diff) / focal_length_;

        // Mark sprite not visible if totally outside bounding box
        if (((*sprite_ptr)->get_x_pixel_position() < bounding_box_left &&
             (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() < bounding_box_left) ||
            ((*sprite_ptr)->get_x_pixel_position() > bounding_box_right &&
             (*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() > bounding_box_right) ||
            ((*sprite_ptr)->get_y_pixel_position() < bounding_box_top &&
             (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() < bounding_box_top) ||
            ((*sprite_ptr)->get_y_pixel_position() > bounding_box_bottom &&
             (*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() > bounding_box_bottom))
        {
            logger_->info("Sprite outside viewable area, not rendering.");
            (*sprite_ptr)->set_visible(false);
            continue;
        }

        // Sprite must be visible then
        (*sprite_ptr)->set_visible(true);

        // Keep track of how many sprites are being rendered
        drawn_sprites_++;

        // Now that sprite is known to be at least partially visible, draw it on the frame

        // First, map sprite location to pixel relative to camera
        //                    (sprite_ptr->get_x_pixel_position() - camera_x_position_) * focal_length_
        //  drawn_left_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_left_pos = ((*sprite_ptr)->get_x_pixel_position() - camera_x_position_) * focal_length_ / z_diff;

        //                     (sprite_ptr->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera_x_position_) * focal_length_
        //  drawn_right_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_right_pos = ((*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera_x_position_) * focal_length_ / z_diff;

        //                    (sprite_ptr->get_y_pixel_position() - camera_y_position_) * focal_length_
        //  drawn_top_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_top_pos = ((*sprite_ptr)->get_y_pixel_position() - camera_y_position_) * focal_length_ / z_diff;

        //                     (sprite_ptr->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera_y_position_) * focal_length_
        //  drawn_bottom_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_bottom_pos = ((*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera_y_position_) * focal_length_ / z_diff;

        // Make values relative to top-left of frame rather than camera
        //drawn_left_pos += frame.get_width() / 2;
        //drawn_right_pos += frame.get_width() / 2;
        //drawn_top_pos += frame.get_height() / 2;
        //drawn_bottom_pos += frame.get_height() / 2;

        // Keep boundaries from going off-frame
        drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos);
        drawn_right_pos = std::min<long unsigned int>(frame.get_width() - 1, drawn_right_pos);
        drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
        drawn_bottom_pos = std::min<long unsigned int>(frame.get_height() - 1, drawn_bottom_pos);

        // Get ratio between z distances
        double z_ratio = (float)(camera_z_position_ - (*sprite_ptr)->get_z_pixel_position()) / focal_length_;

        for (int y = 0; y < (*sprite_ptr)->get_height(); y = (int)(y + z_ratio))
        {
            for (int x = 0; x < (*sprite_ptr)->get_width(); x = (int)(x + z_ratio))
            {
                // Get pixel position relative to sprite
                long int sprite_y = (long int)(y + (*sprite_ptr)->get_y_pixel_position());
                long int sprite_x = (long int)(x + (*sprite_ptr)->get_x_pixel_position());

                // Get pixel of interest
                const taeto::Pixel& sprite_pixel = (*sprite_ptr)->get_pixel(sprite_y, sprite_x);

                // Map from relative to sprite to relative to camera
                long int frame_y = (long int)((sprite_y - camera_y_position_) * focal_length_ / z_diff);
                long int frame_x = (long int)((sprite_x - camera_x_position_) * focal_length_ / z_diff);

                // Map from relative to camera to relative to frame
                frame_y += frame.get_height() / 2;
                frame_x += frame.get_width() / 2;

                taeto::Pixel& frame_pixel = frame.get_pixel(frame_y, frame_x);

                frame_pixel.c = sprite_pixel.c;
            }
        }
    }

    // Update frame number
    update_fps();

    write_debug_info(frame);
}

void RenderSystem::render_frame(taeto::Frame &rendered_frame)
{
    // Get height and width for quick reference
    int h = rendered_frame.get_height();
    int w = rendered_frame.get_width();

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    // Loop over each 'pixel' in frame
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Vector for rendered pixels before they're combined into a single displayed pixel
            static std::vector<taeto::Pixel> pixel_stack = std::vector<taeto::Pixel>();
            pixel_stack.clear();

            // Render each sprite at a time
            for (std::shared_ptr<Sprite> current_sprite : sprites_)
            {
                // Get distance between sprite and camera
                double z_diff = camera_z_position_ - current_sprite->get_z_pixel_position();

                // Make sure sprite is at least in front of the camera and within rendering distance
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (z_diff <= 0 || z_diff > render_distance_)
                    continue;

                // Map frame position to sprite plane position
                double abs_z = current_sprite->get_z_pixel_position();
                double abs_y = (((y - half_frame_height) * z_diff) / focal_length_) + camera_y_position_;
                double abs_x = (((x - half_frame_width) * z_diff) / focal_length_) + camera_x_position_;

                // Map to relative to sprite origin
                double rel_y = abs_y - current_sprite->get_y_pixel_position();
                double rel_x = abs_x - current_sprite->get_x_pixel_position();

                // If pixel doesn't overlap with sprite, move on to next pixel
                if ( rel_x < 0 || rel_x >= current_sprite->get_width() ||
                     rel_y < 0 || rel_y >= current_sprite->get_height())
                     continue;

                // Get pixel of interest
                taeto::Pixel current_pixel = current_sprite->get_pixel(rel_y, rel_x);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be drawn
                if (current_pixel.foreground_color.alpha == 0)
                    continue;

                // Compute lighting for this pixel
                taeto::Color received_light(0, 0, 0);
                for (std::shared_ptr<Light> light : lights_)
                {
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
                pixel_stack.push_back(current_pixel);

                // If this sprite's pixel is fully opaque, we're done rendering this pixel
                if (current_pixel.background_color.alpha == 255)
                    break;
            }

            // Add skybox pixel to stack
            // TODO: SKYBOXES
            taeto::Pixel skybox_pixel = taeto::Pixel(' ', taeto::Color(255, 255, 255, 255), taeto::Color(0, 0, 0, 255), false);
            pixel_stack.push_back(skybox_pixel);

            // Now that we have all the rendered pixels, combine them together
            taeto::Pixel rendered_pixel = pixel_stack.at(pixel_stack.size() - 1);
            for (int i = pixel_stack.size() - 2; i >= 0; --i)
            {
                // Get new background color
                taeto::Color bg = rendered_pixel.background_color & pixel_stack.at(i).background_color;
                rendered_pixel = pixel_stack.at(i);
                rendered_pixel.background_color = bg;
            }

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel(y, x) = rendered_pixel;
        }
    }

    // Keep track of this frame and when it was rendered
    update_fps();
}

void RenderSystem::update_fps()
{
    // Amount of time in milliseconds to average in order to determine FPS
    int const AVERAGING_TIME = 1000;

    // Get milliseconds since epoch for saving when this frame was rendered
    std::chrono::milliseconds time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    // Add time of this frame
    frame_times_.push_back(time);

    // Remove all values in vector that are more than 'averaging_time' milliseconds old
    while(time - frame_times_.front() > std::chrono::milliseconds(AVERAGING_TIME))
        frame_times_.pop_front();

    frame_number_++;

    // Calculate current FPS
    current_fps_ = frame_times_.size() / (AVERAGING_TIME / 1000);
}

void RenderSystem::write_debug_info(taeto::Frame &rendered_frame)
{
    // Print debug information if flag is true
    rendered_frame.add_string(0, 0, "FPS: " + std::to_string(current_fps_));
    rendered_frame.add_string(1, 0, "NUM SPRITES: " + std::to_string(sprites_.size()));
    rendered_frame.add_string(2, 0, "NUM LIGHTS: " + std::to_string(lights_.size()));
    rendered_frame.add_string(3, 0, "CAMERA LOCATION: (" + std::to_string(camera_x_position_) + ", "
                                                         + std::to_string(camera_y_position_) + ", "
                                                         + std::to_string(camera_z_position_) + ")");
    rendered_frame.add_string(4, 0, "FRAME DIMENSIONS: " + std::to_string(rendered_frame.get_width()) + "x"
                                                         + std::to_string(rendered_frame.get_height()));
    rendered_frame.add_string(5, 0, "CURRENT FRAME: " + std::to_string(frame_number_));

    return;
}

}   // namespace taeto
