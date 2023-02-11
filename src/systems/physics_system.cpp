#include "physics_system.h"

PhysicsSystem::PhysicsSystem()
{

}

PhysicsSystem::PhysicsSystem(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

    logger->error("Done setting up physics system.");
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::handle_message(shared_ptr<Message> message)
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
            detect_collisions();
        }
    }
}

void PhysicsSystem::apply_forces()
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

void PhysicsSystem::detect_collisions()
{
    // THIS SHOULD BE REWRITTEN TO HANDLE SUB-FRAME COLLISIONS, BUT RIGHT NOW
    // I JUST WANT RUDIMENTARY COLISION DETECTION, SO JUST DO THE BASICS NOW

    // Compile list of sprites that will collide
    logger->debug("Compiling list of sprites that collide");
    vector<shared_ptr<Sprite>> sprites_that_collide;
    for (auto sprite_pp = sprites.begin(); sprite_pp != sprites.end(); sprite_pp++)
        if ((*sprite_pp)->get_collide())
            sprites_that_collide.push_back((*sprite_pp));

    // Check each sprite
    logger->debug("Checking for collisions");
    for (auto sprite_pp = sprites.begin(); sprite_pp != sprites.end(); sprite_pp++)
    {
        shared_ptr<Sprite> sprite_ptr = (*sprite_pp);

        // Only check if detect collisions is true
        if (sprite_ptr->get_detect_collisions())
        {
            logger->debug("Found sprite that wants to see collisions");

            // Check collisions against every other sprite
            for (auto other_sprite_pp = sprites_that_collide.begin(); other_sprite_pp != sprites_that_collide.end(); other_sprite_pp++)
            {
                shared_ptr<Sprite> other_sprite_ptr = (*other_sprite_pp);

                // Make sure they're not the same sprite
                if (sprite_ptr != other_sprite_ptr)
                {
                    // Notify if they collide
                    if (sprite_ptr->collides_with(other_sprite_ptr))
                    {
                        logger->debug("COLLISION");
                        sprite_ptr->handle_collision(other_sprite_ptr);
                    }
                    else
                    {
                        logger->debug("doesn't collide");
                    }
                }
                else
                {
                    logger->debug("same sprite");
                }
            }
        }
    }
}
