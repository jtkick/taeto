#include "render_system.h"

#include <iostream>

RenderSystem::RenderSystem()
{

}

RenderSystem::RenderSystem(std::shared_ptr<spdlog::logger> l)
{
    logger = l;

    logger->info("Setting up render system.");

    camera_x_position = 0;
    camera_y_position = 0;
    camera_z_position = 0;

    // Drawing plane distance can never be lower than 1
    drawing_plane_distance = 10;

    frame_number = 0;

    logger->info("Done setting up render system.");

    render_distance = 1000000000;
}

RenderSystem::~RenderSystem()
{

}

// TODO: ADD PRIORITY
bool comp(shared_ptr<Sprite> a, shared_ptr<Sprite> b) { return !(a->z_position <= b->z_position); }
            std::sort(sprites.begin(), sprites.end(), comp);

void RenderSystem::render_frame_by_drawing(shared_ptr<Frame> frame)
{
    write_alpha_background(frame);

    // Initizlize counters
    drawn_sprites = 0;

    // Quick sanity check
    if (drawing_plane_distance < 1)
    {
        logger->error("Drawing plane distance set to: " + std::to_string(drawing_plane_distance));
        return;
    }

    logger->info("Number of sprites known to render system: " + std::to_string(sprites.size()));

    // Find all sprites that are going to be drawn
    for (auto sprite_ptr = sprites.begin(); sprite_ptr != sprites.end(); sprite_ptr++)
    {
        // If beyond render distance, move on
        if (camera_z_position - (*sprite_ptr)->get_z_pixel_position() > render_distance ||
            (*sprite_ptr)->get_z_pixel_position() >= camera_z_position)
        {
            logger->info("Sprite out of visible range, not rendering.");
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
        //             / |    | <------- camera_z_position - current_sprite->get_z_pixel_position()
        //            /  | <------------ drawing_plane_distance
        //           /   |    |
        //         _/____|____|
        //         \_/ ^    ^----- bounding_box_(left/right/top/bottom)
        //         | | └---------- (x/y)
        //          ¯
        //          ^- camera
        //

        double z_diff = camera_z_position - (*sprite_ptr)->get_z_pixel_position();

        //                                           -(frame->get_width() / 2) * z_diff
        //  bounding_box_left = camera_x_position + -----------------------------------
        //                                                drawing_plane_distance
        long int bounding_box_left = camera_x_position + (-((float)frame->get_width() / 2) * z_diff) / drawing_plane_distance;

        //                                            (frame->get_width() + 1) / 2) * z_diff
        //  bounding_box_right = camera_x_position + ---------------------------------------
        //                                                   drawing_plane_distance
        long int bounding_box_right = camera_x_position + ((((float)frame->get_width() + 1) / 2) * z_diff) / drawing_plane_distance;

        //                                          -(frame->get_height() / 2) * z_diff
        //  bounding_box_top = camera_y_position + ------------------------------------
        //                                                drawing_plane_distance
        long int bounding_box_top = camera_y_position + (-((float)frame->get_height() / 2) * z_diff) / drawing_plane_distance;

        //                                            (frame->get_height() + 1) / 2) * z_diff
        //  bounding_box_bottom = camera_y_position + ---------------------------------------
        //                                                   drawing_plane_distance
        long int bounding_box_bottom = camera_y_position + ((((float)frame->get_height() + 1) / 2) * z_diff) / drawing_plane_distance;

        logger->error("dpd: " + std::to_string(drawing_plane_distance));
        logger->error("zdiff: " + std::to_string(z_diff));
        logger->error("bbl: " + std::to_string(bounding_box_left));
        logger->error("bbr: " + std::to_string(bounding_box_right));
        logger->error("bbt: " + std::to_string(bounding_box_top));
        logger->error("bbb: " + std::to_string(bounding_box_bottom));

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
            logger->info("Sprite outside viewable area, not rendering.");
            (*sprite_ptr)->set_visible(false);
            continue;
        }

        // Sprite must be visible then
        (*sprite_ptr)->set_visible(true);

        // Keep track of how many sprites are being rendered
        drawn_sprites++;

        // Now that sprite is known to be at least partially visible, draw it on the frame

        // First, map sprite location to pixel relative to camera
        //                    (sprite_ptr->get_x_pixel_position() - camera_x_position) * drawing_plane_distance
        //  drawn_left_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_left_pos = ((*sprite_ptr)->get_x_pixel_position() - camera_x_position) * drawing_plane_distance / z_diff;

        //                     (sprite_ptr->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera_x_position) * drawing_plane_distance
        //  drawn_right_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_right_pos = ((*sprite_ptr)->get_x_pixel_position() + (*sprite_ptr)->get_width() - camera_x_position) * drawing_plane_distance / z_diff;

        //                    (sprite_ptr->get_y_pixel_position() - camera_y_position) * drawing_plane_distance
        //  drawn_top_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_top_pos = ((*sprite_ptr)->get_y_pixel_position() - camera_y_position) * drawing_plane_distance / z_diff;

        //                     (sprite_ptr->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera_y_position) * drawing_plane_distance
        //  drawn_bottom_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_bottom_pos = ((*sprite_ptr)->get_y_pixel_position() + (*sprite_ptr)->get_height() - camera_y_position) * drawing_plane_distance / z_diff;

        // Make values relative to top-left of frame rather than camera
        //drawn_left_pos += frame->get_width() / 2;
        //drawn_right_pos += frame->get_width() / 2;
        //drawn_top_pos += frame->get_height() / 2;
        //drawn_bottom_pos += frame->get_height() / 2;

        // Keep boundaries from going off-frame
        drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos);
        drawn_right_pos = std::min<long unsigned int>(frame->get_width() - 1, drawn_right_pos);
        drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
        drawn_bottom_pos = std::min<long unsigned int>(frame->get_height() - 1, drawn_bottom_pos);

        logger->error("drawn left pos: " + std::to_string(drawn_left_pos));
        logger->error("drawn right pos: " + std::to_string(drawn_right_pos));
        logger->error("drawn top pos: " + std::to_string(drawn_top_pos));
        logger->error("drawn bottom pos: " + std::to_string(drawn_bottom_pos));

        // Get ratio between z distances
        double z_ratio = (float)(camera_z_position - (*sprite_ptr)->get_z_pixel_position()) / drawing_plane_distance;

        logger->error("Sprite height: " + std::to_string((*sprite_ptr)->get_height()));
        logger->error("Sprite width: " + std::to_string((*sprite_ptr)->get_width()));

        for (int y = 0; y < (*sprite_ptr)->get_height(); y = (int)(y + z_ratio))
        {
            for (int x = 0; x < (*sprite_ptr)->get_width(); x = (int)(x + z_ratio))
            {
                // Get pixel position relative to sprite
                long int sprite_y = (long int)(y + (*sprite_ptr)->get_y_pixel_position());
                long int sprite_x = (long int)(x + (*sprite_ptr)->get_x_pixel_position());

                // Get pixel of interest
                logger->error("Getting sprite pixel: (" + std::to_string(sprite_y) + ", " + std::to_string(sprite_x) + ")");
                const Pixel& sprite_pixel = (*sprite_ptr)->get_pixel(sprite_y, sprite_x);

                // Map from relative to sprite to relative to camera
                long int frame_y = (long int)((sprite_y - camera_y_position) * drawing_plane_distance / z_diff);
                long int frame_x = (long int)((sprite_x - camera_x_position) * drawing_plane_distance / z_diff);

                // Map from relative to camera to relative to frame
                frame_y += frame->get_height() / 2;
                frame_x += frame->get_width() / 2;

                logger->error("Frame y: " + std::to_string(frame_y));
                logger->error("Frame x: " + std::to_string(frame_x));

                Pixel& frame_pixel = frame->get_pixel(frame_y, frame_x);

                logger->error("Char: " + std::to_string(sprite_pixel.c));

                frame_pixel.c = sprite_pixel.c;
            }
        }
    }

    update_fps();

    write_debug_info(frame);
}


/**
 * Render a PixelFrame with all known objects in the engine. Uses a ray-casting type method and deferred lighting.
 *
 * @param rendered_frame Frame to write rendered pixels to.
*/
void RenderSystem::render_frame(Frame& rendered_frame)
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
            vector<Pixel> pixel_stack = vector<Pixel>();
            pixel_stack.clear();

            // Render each sprite at a time
            for (shared_ptr<Sprite> current_sprite : sprites)
            {
                // Get distance between sprite and camera
                double z_diff = camera_z_position - current_sprite->get_z_pixel_position();

                // Make sure sprite is at least in front of the camera
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (z_diff <= 0)
                    continue;

                // Map frame position to sprite plane position
                double abs_z = current_sprite->get_z_pixel_position();
                double abs_y = (((y - half_frame_height) * z_diff) / drawing_plane_distance) + camera_y_position;
                double abs_x = (((x - half_frame_width) * z_diff) / drawing_plane_distance) + camera_x_position;

                // Map to relative to sprite origin
                double rel_y = abs_y - current_sprite->get_y_pixel_position();
                double rel_x = abs_x - current_sprite->get_x_pixel_position();

                // If pixel doesn't overlap with sprite, move on to next pixel
                if ( rel_x < 0 || rel_x >= current_sprite->get_width() ||
                     rel_y < 0 || rel_y >= current_sprite->get_height())
                     continue;

                // Get pixel of interest
                Pixel current_pixel = current_sprite->get_pixel(rel_y, rel_x);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be drawn
                if (current_pixel.foreground_color.alpha == 0)
                    continue;

                // Compute lighting for this pixel
                Color received_light(0, 0, 0);
                for (std::shared_ptr<Light> light : lights)
                {
                    // Light color at this pixel location
                    Color light_color = light->get_color(abs_x, abs_y, abs_z);

                    // Get light vector and pixel normal
                    const Vector& pixel_normal = current_pixel.normal;
                    const Vector light_vector = light->get_vector(abs_x, abs_y, abs_z);

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
            Pixel skybox_pixel = Pixel(' ', Color(255, 255, 255, 255), Color(0, 0, 0, 255), false);
            pixel_stack.push_back(skybox_pixel);

            // Now that we have all the rendered pixels, combine them together
            Pixel rendered_pixel = pixel_stack.at(pixel_stack.size() - 1);
            for (int i = pixel_stack.size() - 2; i >= 0; --i)
            {
                // Get new background color
                Color bg = rendered_pixel.background_color & pixel_stack.at(i).background_color;
                rendered_pixel = pixel_stack.at(i);
                rendered_pixel.background_color = bg;
            }

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel(y, x) = rendered_pixel;
        }
    }
}

void RenderSystem::update_fps()
{
    // Get milliseconds since epoch for saving when this frame was rendered
    milliseconds time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    // Add time of this frame
    frame_times.push_back(time);

    // Remove all values in vector that are more than 'averaging_time' milliseconds old
    while(time - frame_times.front() > milliseconds(averaging_time))
        frame_times.pop_front();

    // Calculate current FPS
    current_fps = frame_times.size() / (averaging_time / 1000);
}


void RenderSystem::write_alpha_background(shared_ptr<Frame> rendered_frame)
{
    int h = rendered_frame->get_height();
    int w = rendered_frame->get_width();

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    int size = 1;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Get current pixel of frame
            Pixel& rendered_pixel = rendered_frame->get_pixel(y, x);

            rendered_pixel.clear();

            if ( (x % 4 < 2) != (y % 2 < 1) )
            {
                rendered_pixel.background_color = Color(255, 255, 255);
            }
            else
            {
                rendered_pixel.background_color = Color(127, 127, 127);
            }
        }
    }
}


void RenderSystem::write_color_bars(shared_ptr<Frame> rendered_frame)
{
    int h = rendered_frame->get_height();
    int w = rendered_frame->get_width();

    int end_first_row = (int)((double)h * 0.7);
    int curr_col = 0;
}


void RenderSystem::write_debug_info(shared_ptr<Frame> rendered_frame)
{
    // Print debug information if flag is true
    rendered_frame->add_string(0, 0, "FPS: " + std::to_string(current_fps));
    rendered_frame->add_string(1, 0, "NUM SPRITES: " + std::to_string(sprites.size()));
    rendered_frame->add_string(2, 0, "NUM LIGHTS: " + std::to_string(lights.size()));
    rendered_frame->add_string(3, 0, "CAMERA LOCATION: (" + std::to_string(camera_x_position) + ", "
                                                          + std::to_string(camera_y_position) + ", "
                                                          + std::to_string(camera_z_position) + ")");
    rendered_frame->add_string(4, 0, "FRAME DIMENSIONS: " + std::to_string(rendered_frame->get_width()) + "x"
                                                          + std::to_string(rendered_frame->get_height()));
    rendered_frame->add_string(5, 0, "CURRENT FRAME: " + std::to_string(frame_number++));
    rendered_frame->add_string(6, 0, "WILL TO LIVE: 1");

    return;
}
