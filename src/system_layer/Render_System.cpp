
Render_System::Render_System()
{

}

Render_System::handle_message(Message* message)
{

    // Handle messages types this system cares about
    switch(message->get_id())
    {

        case ADD_SPRITE:

            // Keep track of sprite
            sprites.push_back(message->get_sprite_ptr());

            break;

        case ADD_LIGHT:

            // Keep track of light
            lights.push_back(message->get_light_ptr());

            break;

        case RENDER_FRAME:

            // Render to shared frame
            render_frame(message->get_frame_ptr());

            break;

        case MOVE_CAMERA:

            // Move camera to given x, y, and z location
            camera_x_position = message->get_x_position();
            camera_y_position = message->get_y_position();
            camera_z_position = message->get_z_position();

            break;

    }
}
