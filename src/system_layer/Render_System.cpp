#include "Render_System.h"

Render_System::Render_System()
{

    camera_x_position = 0;
    camera_y_position = 0;
    camera_z_position = 0;
}

Render_System::~Render_System()
{

}

void Render_System::handle_message(unique_ptr<Message> message)
{

    // Handle messages types this system cares about
    switch(message->get_id())
    {

        case ADD_SPRITE:

            // Keep track of sprite
            //sprites.push_back(message.get_sprite());

            break;

        case ADD_LIGHT:

            // Keep track of light
            //lights.push_back(message.get_light());

            break;

        case RENDER_FRAME:

            // Render to shared frame
            //render_frame(message.get_frame());

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

void Render_System::render_frame(Frame &frame)
{

    // Initizlize counters
    drawn_sprites = 0;

    // Find all sprites that are going to be drawn
    for (auto sprite_ptr = sprites.begin(); sprite_ptr != sprites.end(); sprite_ptr++)
    {
        // If beyond render distance, move on
        if (camera_z_position - (*sprite_ptr)->get_z_position() < render_distance ||
            (*sprite_ptr)->get_z_position() >= camera_z_position)
        {
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

        //                                           -(frame.get_width() / 2) * z_diff
        //  bounding_box_left = camera_x_position + -----------------------------------
        //                                                drawing_plane_distance
        long int bounding_box_left = camera_x_position + (-((float)frame.get_width() / 2) * z_diff) / drawing_plane_distance;

        //                                            (frame.get_width() + 1) / 2) * z_diff
        //  bounding_box_right = camera_x_position + ---------------------------------------
        //                                                   drawing_plane_distance
        long int bounding_box_right = camera_x_position + ((((float)frame.get_width() + 1) / 2) * z_diff) / drawing_plane_distance;

        //                                          -(frame.get_height() / 2) * z_diff
        //  bounding_box_top = camera_y_position + ------------------------------------
        //                                                drawing_plane_distance
        long int bounding_box_top = camera_y_position + (-((float)frame.get_height() / 2) * z_diff) / drawing_plane_distance;

        //                                            (frame.get_height() + 1) / 2) * z_diff
        //  bounding_box_bottom = camera_y_position + ---------------------------------------
        //                                                   drawing_plane_distance
        long int bounding_box_bottom = camera_y_position + ((((float)frame.get_height() + 1) / 2) * z_diff) / drawing_plane_distance;

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
        drawn_left_pos += frame.get_width() / 2;
        drawn_right_pos += frame.get_height() / 2;

        // Keep boundaries from going off-frame
        drawn_left_pos = std::max<long unsigned int>(0, drawn_left_pos + (frame.get_width() / 2));
        drawn_right_pos = std::min<long unsigned int>(frame.get_width() - 1, drawn_left_pos);
        drawn_top_pos = std::max<long unsigned int>(0, drawn_top_pos);
        drawn_bottom_pos = std::min<long unsigned int>(frame.get_height() - 1, drawn_bottom_pos);

        for (int x = drawn_left_pos; x < drawn_right_pos; x++)
        {
            for (int y = drawn_top_pos; y < drawn_top_pos; y++)
            {
                // Map drawn pixel to sprite pixel
                //                                        (x - (frame.get_width() / 2)) * z_diff
                //  sprite_plane_x = camera_x_position + ----------------------------------------
                //                                                drawing_plane_distance
                long int sprite_plane_x = camera_x_position + ((x - ((float)frame.get_width() / 2)) * z_diff) / drawing_plane_distance;

                //                                        (y - (frame.get_height() / 2)) * z_diff
                //  sprite_plane_y = camera_y_position + ----------------------------------------
                //                                                drawing_plane_distance
                long int sprite_plane_y = camera_y_position + ((y - ((float)frame.get_height() / 2)) * z_diff) / drawing_plane_distance;

                // Convert to absolute position to relative to sprite position
                sprite_plane_x -= (*sprite_ptr)->get_x_position();
                sprite_plane_y -= (*sprite_ptr)->get_y_position();

                // Get pixel of interest
                unique_ptr<Pixel> sprite_pixel = (*sprite_ptr)->get_pixel(sprite_plane_x, sprite_plane_y);

                unique_ptr<Pixel> frame_pixel = (*sprite_ptr)->get_pixel(x, y);

                frame_pixel->set_char(sprite_pixel->get_char());
            }
        }
    }

    // Get milliseconds since epoch for saving when this frame was rendered
    milliseconds time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    // Remove all values in vector that are more than 'averaging_time' milliseconds old
    while(time - frame_times.front() > milliseconds(averaging_time))
        frame_times.pop_front();

    // Now add time of this frame
    frame_times.push_back(time);

    // Calculate current FPS
    current_fps = frame_times.size() / (averaging_time / 1000);

}
