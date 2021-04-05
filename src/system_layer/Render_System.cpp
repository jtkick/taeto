#include "Render_System.h"

Render_System::Render_System()
{
    camera_x_position = 0;
    camera_y_position = 0;
    camera_z_position = 0;

    // Drawing plane distance can never be lower than 1
    drawing_plane_distance = 10;
}

Render_System::Render_System(shared_ptr<spdlog::logger> l)
{
    logger = l;

    camera_x_position = 0;
    camera_y_position = 0;
    camera_z_position = 0;

    // Drawing plane distance can never be lower than 1
    drawing_plane_distance = 10;
}

Render_System::~Render_System()
{

}

void Render_System::handle_message(shared_ptr<Message> message)
{

    // Handle messages types this system cares about
    switch(message->get_id())
    {

        case SPRITE_UPDATE:
        {
            logger->info("Sprite update message received.");

            shared_ptr<Sprite_Update_Message> sum = dynamic_pointer_cast<Sprite_Update_Message>(message);

            // Keep track of sprite
            sprites.push_back(sum->get_sprite());

        }
        break;

        case LIGHT_UPDATE:

            // Keep track of light
            //lights.push_back(message.get_light());

            break;

        case RENDER_FRAME:
        {
            logger->info("Render frame message received.");

            shared_ptr<Render_Frame_Message> rfm = dynamic_pointer_cast<Render_Frame_Message>(message);

            // Render to shared frame
            render_frame(rfm->get_frame());
        }
        break;

        case MOVE_CAMERA:

            // Move camera to given x, y, and z location
            //camera_x_position = message.get_x_position();
            //camera_y_position = message.get_y_position();
            //camera_z_position = message.get_z_position();

            break;

    }
}

//  __________________________
// |     _              _     |
// |   _/ \            / \_   |
// |  |__  \ ________ /  __|  |
// |     \  /        \  /     |
// |      \| ___  ___ |/      |
// |       | \_/  \_/ |       |
// |       (__  /\  __)       |
// |         \\MMMM//         |
// |         /\MMMM/\         |
// |        /  /  \  \        |
// |     __/  /    \  \__     |
// |    |_   /      \   _|    |
// |      \_/        \_/      |
// |                          |
// |  Lasciate ogni speranza, |
// |      voi ch'entrate.     |
// |__________________________|
//

void Render_System::render_frame(shared_ptr<Frame> frame)
{
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
        logger->error("rendering");

        // If beyond render distance, move on
        if (camera_z_position - (*sprite_ptr)->get_z_position() < render_distance ||
            (*sprite_ptr)->get_z_position() >= camera_z_position)
        {
            logger->error("not visible");
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
        //             / |    | <------- z_camera_position - current_sprite->get_z_position()
        //            /  | <------------ drawing_plane_distance
        //           /   |    |
        //         _/____|____|
        //         \_/ ^    ^----- bounding_box_(left/right/top/bottom)
        //         | | └---------- (x/y)
        //          ¯
        //          ^- camera
        //

        long int z_diff = camera_z_position - (*sprite_ptr)->get_z_position();

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
        if (((*sprite_ptr)->get_x_position() < bounding_box_left &&
             (*sprite_ptr)->get_x_position() + (*sprite_ptr)->get_width() < bounding_box_left) ||
            ((*sprite_ptr)->get_x_position() > bounding_box_right &&
             (*sprite_ptr)->get_x_position() + (*sprite_ptr)->get_width() > bounding_box_right) ||
            ((*sprite_ptr)->get_y_position() < bounding_box_top &&
             (*sprite_ptr)->get_y_position() + (*sprite_ptr)->get_height() < bounding_box_top) ||
            ((*sprite_ptr)->get_y_position() > bounding_box_bottom &&
             (*sprite_ptr)->get_y_position() + (*sprite_ptr)->get_height() > bounding_box_bottom))
        {
            logger->error("outside bounding box");
            (*sprite_ptr)->set_visible(false);
            continue;
        }

        // Keep track of how many sprites are being rendered
        drawn_sprites++;

        // Now that sprite is known to be at least partially visible, draw it on the frame

        // First, map sprite location to pixel relative to camera
        //                    (sprite_ptr->get_x_position() - camera_x_position) * drawing_plane_distance
        //  drawn_left_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_left_pos = ((*sprite_ptr)->get_x_position() - camera_x_position) * drawing_plane_distance / z_diff;

        //                     (sprite_ptr->get_x_position() + (*sprite_ptr)->get_width() - camera_x_position) * drawing_plane_distance
        //  drawn_right_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_right_pos = ((*sprite_ptr)->get_x_position() + (*sprite_ptr)->get_width() - camera_x_position) * drawing_plane_distance / z_diff;

        //                    (sprite_ptr->get_y_position() - camera_y_position) * drawing_plane_distance
        //  drawn_top_pos = -----------------------------------------------------------------------------
        //                                                 z_diff
        long int drawn_top_pos = ((*sprite_ptr)->get_y_position() - camera_y_position) * drawing_plane_distance / z_diff;

        //                     (sprite_ptr->get_y_position() + (*sprite_ptr)->get_height() - camera_y_position) * drawing_plane_distance
        //  drawn_bottom_pos = -------------------------------------------------------------------------------------------------------
        //                                                                  z_diff
        long int drawn_bottom_pos = ((*sprite_ptr)->get_y_position() + (*sprite_ptr)->get_height() - camera_y_position) * drawing_plane_distance / z_diff;

        // Make values relative to top-left of frame rather than camera
        drawn_left_pos += frame->get_width() / 2;
        drawn_right_pos += frame->get_width() / 2;
        drawn_top_pos += frame->get_height() / 2;
        drawn_bottom_pos += frame->get_height() / 2;

        // Keep boundaries from going off-frame
        drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos);
        drawn_right_pos = std::min<long unsigned int>(frame->get_width() - 1, drawn_right_pos);
        drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
        drawn_bottom_pos = std::min<long unsigned int>(frame->get_height() - 1, drawn_bottom_pos);

        logger->error("drawn left pos: " + std::to_string(drawn_left_pos));
        logger->error("drawn right pos: " + std::to_string(drawn_right_pos));
        logger->error("drawn top pos: " + std::to_string(drawn_top_pos));
        logger->error("drawn bottom pos: " + std::to_string(drawn_bottom_pos));

        // TODO: Y THEN X
        for (int x = drawn_left_pos; x < drawn_right_pos; x++)
        {
            for (int y = drawn_top_pos; y < drawn_bottom_pos; y++)
            {
                // Map drawn pixel to sprite pixel
                //                                        (x - (frame->get_width() / 2)) * z_diff
                //  sprite_plane_x = camera_x_position + ----------------------------------------
                //                                                drawing_plane_distance
                long int sprite_plane_x = camera_x_position + ((x - ((float)frame->get_width() / 2)) * z_diff) / drawing_plane_distance;

                //                                        (y - (frame->get_height() / 2)) * z_diff
                //  sprite_plane_y = camera_y_position + ----------------------------------------
                //                                                drawing_plane_distance
                long int sprite_plane_y = camera_y_position + ((y - ((float)frame->get_height() / 2)) * z_diff) / drawing_plane_distance;

                // Convert to absolute position to relative to sprite position
                sprite_plane_x -= (*sprite_ptr)->get_x_position();
                sprite_plane_y -= (*sprite_ptr)->get_y_position();

                // Get pixel of interest
                logger->error("Getting pixel: (" + std::to_string(sprite_plane_y) + ", " + std::to_string(sprite_plane_x) + ")");
                unique_ptr<Pixel> sprite_pixel = (*sprite_ptr)->get_pixel(sprite_plane_y, sprite_plane_x);

                unique_ptr<Pixel> frame_pixel = frame->get_pixel(y, x);

                frame_pixel->set_char(sprite_pixel->get_char());

                logger->error(std::to_string(sprite_pixel->get_char()));
            }
        }
    }

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



/////////////////////////////////////
////      OLD RENDER METHOD      ////
/////////////////////////////////////
/*
// This method iterates over all sprites known to the engine, and renders a
// frame with them.
void Engine::render_frame(Frame* rendered_frame)
{
    // Create frame for window
    //int h, w;
    //getmaxyx(stdscr, h, w);

    //Frame f(h, w);

    // Loop over each 'pixel' in frame
    int h = rendered_frame->get_height();
    for (int y = 0; y < h; y++)
    {
        // Create row
        //vector<pixel> line;

        int w = rendered_frame->get_width();
        for (int x = 0; x < rendered_frame->get_width(); x++)
        {
            // Get current pixel of frame
            Pixel *rendered_pixel = rendered_frame->get_pixel(y, x);

            // Reset pixel
            rendered_pixel->clear();

            // Loop over each sprite, and write to current frame
            //vector<Sprite*>::iterator sprite;
            //for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)
            for (int sprite_num = 0, size = sprites.size(); sprite_num < size; sprite_num++)
            {
                Sprite* current_sprite = sprites[sprite_num];

                // Get distance between sprite and camera
                long int z_diff = z_camera_position - current_sprite->get_z_position();

                // Make sure sprite is at least in front of the camera
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (z_diff <= 0)
                    continue;

                // Get absolute position of pixel taking distance from camera into account
                long int abs_x = x_camera_position - (w / 2) * z_diff + x * z_diff;
                long int abs_y = y_camera_position - (h / 2) * z_diff + y * z_diff;

                // Get pixel relative to sprite
                long int rel_x = abs_x - current_sprite->get_x_position();
                long int rel_y = abs_y - current_sprite->get_y_position();

                // Get sprite dimensions
                //long int sprite_width = current_sprite->get_width();
                //long int sprite_height = current_sprite->get_height();

                // Get index relative to sprite size
                rel_x = (rel_x / z_diff) - 1;
                rel_y = (rel_y / z_diff) - 1;

                // If pixel overlaps with sprite
                if ( 0 <= rel_x && rel_x < current_sprite->get_width() &&
                     0 <= rel_y && rel_y < current_sprite->get_height())
                {
                    // Get pixel of interest
                    Pixel *current_pixel = current_sprite->get_pixel(rel_x, rel_y);

                    // Determine if pixel should be drawn
                    // If the foreground alpha channel is anything but 0, it will be drawn
                    if (current_pixel->get_foreground_color()->get_alpha() != 0)
                    {
                        // Write character to pixel
                        rendered_pixel->set_char(current_pixel->get_char());

                        // TODO: THIS PROBABLY WON'T WORK FOR TRANSPARENT COLORS
                        // Write initial colors to pixel
                        rendered_pixel->set_foreground_color(*(current_pixel->get_foreground_color()));
                        rendered_pixel->set_background_color(*(current_pixel->get_background_color()));

                        // Handle dynamic lighting
                        if (current_sprite->respects_light_sources())
                        {
                            Color c;

                            // Calculate new color based on nearby light sources
                            // Iterate over all light sources known to the engine
                            for (int light_num = 0, size = lights.size(); light_num < size; light_num++)
                            {
                                Light* current_light = lights[light_num];

                                long int abs_x = current_sprite->get_x_position() + rel_x;
                                long int abs_y = current_sprite->get_y_position() + rel_y;
                                long int abs_z = current_sprite->get_z_position();

                                // Light color at location
                                c = current_light->get_color(abs_x, abs_y, abs_z);

                                // Compare normals to get light intensity
                                if (current_sprite->compare_normals())
                                {
                                    // Get vectors
                                    const Vector* pixel_normal = current_pixel->get_normal();
                                    const Vector light_vector = current_light->get_vector(abs_x, abs_y, abs_z);

                                    // Get vector components
                                    char x1 = pixel_normal->get_x_component();
                                    char y1 = pixel_normal->get_y_component();
                                    char z1 = pixel_normal->get_z_component();
                                    char x2 = light_vector.get_x_component();
                                    char y2 = light_vector.get_y_component();
                                    char z2 = light_vector.get_z_component();

                                    // Calculate angle between the two
                                    float angle = acos((x1 * x2 + y1 * y2 + z1 * z2) / (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) * sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2))));

                                    // Scale from 0 to pi, to between 0 and 255
                                    unsigned char brightness = 255 - (unsigned char)(angle * 81.1690378636);

                                    // Adjust light brightness accordingly
                                    c.set_brightness(brightness);
                                }

                                rendered_pixel->set_foreground_color(c * (*(rendered_pixel->get_foreground_color())));
                                rendered_pixel->set_background_color(c * (*(rendered_pixel->get_background_color())));
                            }
                        }
                        else
                        {
                            // Write foreground color to pixel
                            rendered_pixel->set_foreground_color(*(current_pixel->get_foreground_color()));
                            rendered_pixel->set_background_color(*(current_pixel->get_background_color()));
                        }

                        // Write bold to pixel
                        rendered_pixel->set_bold(current_pixel->get_bold());

                        // Write underline to pixel
                        rendered_pixel->set_underline(current_pixel->get_underline());
                    }

                }

            }

            // Write pixel to line
            //f.set_pixel(y, x, frame_pixel);
        }

    }

    static unsigned int frames;

    // Keep track of number of frames until second elapses
    long long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    if (now - last_count_time > 1000)
    {
        actual_frame_rate = frames;
        frames = 0;

        // Last run time
        last_count_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    }

    rendered_frame->add_string(1, 0, "FPS: " + std::to_string(actual_frame_rate));
    rendered_frame->add_string(2, 0, "NUM SPRITES: " + std::to_string(sprites.size()));
    rendered_frame->add_string(3, 0, "NUM LIGHTS: " + std::to_string(lights.size()));
    rendered_frame->add_string(4, 0, "CAMERA LOCATION: (" + std::to_string(x_camera_position) + ", "
                                                          + std::to_string(y_camera_position) + ", "
                                                          + std::to_string(z_camera_position) + ")");
    rendered_frame->add_string(5, 0, "WILL TO LIVE: " + std::to_string(0));


    frames++;

    return;

}
*/
