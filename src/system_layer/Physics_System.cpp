#include "Physics_System.h"

Physics_System::Physics_System(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

    logger->error("Done setting up physics system.");
}

Physics_System::~Physics_System()
{

}

void Physics_System::handle_message(shared_ptr<Message> message)
{
    // Handle message types this system cares about
    switch (message->get_id())
    {
        case SPRITE_UPDATE:
        {
            // Keep track of sprite
            shared_ptr<Sprite_Update_Message> sum = dynamic_pointer_cast<Sprite_Update_Message>(message);
            sprites.push_back(sum->get_sprite());
        }
        break;

        case APPLY_FORCES:
        {
            apply_forces();
        }
    }
}

void Physics_System::apply_forces()
{
    for (auto sprite_ptr = sprites.begin(); sprite_ptr != sprites.end(); sprite_ptr++)
    {
        // Get sprite mass and forces
        double mass = (*sprite_ptr)->get_mass();
        double fx = (*sprite_ptr)->get_x_force();
        double fy = (*sprite_ptr)->get_y_force();
        double fz = (*sprite_ptr)->get_z_force();

        // Calculate accelerations
        double ax = fx / mass;
        double ay = fy / mass;
        double az = fz / mass;

        // Get current time in milliseconds
        long long current_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

        // Get time since physics last applied to this sprite
        double time_since_last_applied = (double)current_time - (double)(*sprite_ptr)->get_time_physics_last_applied();
        (*sprite_ptr)->set_time_physics_last_applied(current_time);

        // Get in seconds
        time_since_last_applied /= 1000;

        // Add accumulated speed to current speed
        (*sprite_ptr)->set_x_speed((*sprite_ptr)->get_x_speed() + (ax * time_since_last_applied));
        (*sprite_ptr)->set_y_speed((*sprite_ptr)->get_y_speed() + (ay * time_since_last_applied));
        (*sprite_ptr)->set_z_speed((*sprite_ptr)->get_z_speed() + (az * time_since_last_applied));


        // TODO: MOVE THIS TO COLLISION DETECTION
        // Update position
        (*sprite_ptr)->set_x_exact_position((*sprite_ptr)->get_x_exact_position() + ((*sprite_ptr)->get_x_speed() * time_since_last_applied));
        (*sprite_ptr)->set_y_exact_position((*sprite_ptr)->get_y_exact_position() + ((*sprite_ptr)->get_y_speed() * time_since_last_applied));
        (*sprite_ptr)->set_z_exact_position((*sprite_ptr)->get_z_exact_position() + ((*sprite_ptr)->get_z_speed() * time_since_last_applied));
    }
}

void Physics_System::detect_collisions()
{

}
