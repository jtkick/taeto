#include "Zero.h"

Zero::Zero()
{
    // Default position to the origin
    x_position = 0;
    y_position = -10;
    z_position = 0;

    // Set frame details
    height = 2;
    width = 6;

    mass = 1;
    y_force = 250000000000;

    collide = true;
    detect_collisions = true;

    //current_frame = new Frame(7, 7);
    Frame f = Frame(height, width);

    Color w = Color(255, 255, 255);
    Color g = Color(43, 43, 43);
    Color a = Color(255, 255, 255, 0);

    f.set_chars({ R"(@@__@@)",
                  R"(@( ')')"});
    f.set_foreground_colors( { { a, a, g, g, a, a },
                               { a, g, g, g, g, g } } );
    f.set_background_colors( { { w, w, a, a, w, w },
                               { w, w, w, w, w, w } } );
    frames.insert(std::make_pair("forward", f));

    f.set_chars({ R"(@@__@@)",
                  R"('(' )@)"});
    f.set_foreground_colors( { { a, a, g, g, a, a },
                               { g, g, g, g, g, a } } );
    f.set_background_colors( { { w, w, a, a, w, w },
                               { w, w, w, w, w, w } } );
    frames.insert(std::make_pair("backward", f));

    current_frame = frames["forward"];



    respect_light_sources = true;

    jump_timer = DEFAULT_JUMP_TIME;
}

void Zero::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    // Handle floor collision
    if ((sprite_ptr->get_tags() & FLOOR_TAG) == FLOOR_TAG)
    {
        // Reset jump timer
        jump_timer = DEFAULT_JUMP_TIME;

        // Null y speed
        this->set_y_speed(0.0);

        // Slow x speed
        //this->set_x_speed(this->get_x_speed() * 0.9);

        // Move up
        while (this->collides_with(sprite_ptr))
            this->set_y_pixel_position(this->get_y_pixel_position() - 1);
    }

    // Handle wall collision
    if ((sprite_ptr->get_tags() & WALL_TAG) == WALL_TAG)
    {
        if (this->get_x_speed() >= 0)
        {
            // Move left
            while (this->collides_with(sprite_ptr))
                this->set_x_pixel_position(this->get_x_pixel_position() - 1);
        }
        else if (this->get_x_speed() < 0)
        {
            // Move right
            while (this->collides_with(sprite_ptr))
                this->set_x_pixel_position(this->get_x_pixel_position() + 1);
        }
    }
}

void Zero::handle_message(shared_ptr<Message> message)
{
    switch (message->get_id())
    {
        case ANIMATE:
        {
            // Set default Y physics
            set_y_force(500000000000);

            // Whether jump button has been released
            bool jump_released;

            // Handle jump
            if (w || space)
            {
                // Push Zero up if timer hasn't run out yet
                if (jump_timer > milliseconds(0))
                {
                    set_y_force(0);
                    set_y_speed(-130000000000);
                }

                // Start counting down timer
                jump_timer = (jump_timer - (duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - last_animate_call));
            }

            // Handle X movement
            if (a)
            {
                set_x_force(-500000000000.0);
            }
            if (d)
            {
                set_x_force(500000000000.0);
            }
            if (a == d)
            {
                // Stop pushing Zero
                set_x_force(0);

                // Start tapering speed
                x_speed = x_speed * 0.9;
            }

            // Cap Zero's speed
            //set_x_speed(get_x_speed() * 0.9);

            x_speed = x_speed < 300000000000 ? x_speed : 300000000000;
            x_speed = x_speed > -300000000000 ? x_speed : -300000000000;

            // Update which direction Zero is facing
            if (a && !d)
            {
                set_current_frame("backward");
            }
            else if (!a && d)
            {
                set_current_frame("forward");
            }

            // Update animate time
            last_animate_call = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }
        break;

        case KEY_UPDATE:
        {
            //logger->info("TEST SCENE RECEIVED KEY UPDATE");

            shared_ptr<Key_Update_Message> kum = dynamic_pointer_cast<Key_Update_Message>(message);

            // Move camera based on key
            switch(kum->get_key())
            {
                case ' ':
                    space = kum->is_pressed();
                break;

                case 'w':
                    w = kum->is_pressed();
                break;

                case 'a':
                    a = kum->is_pressed();
                break;

                case 's':
                    s = kum->is_pressed();
                break;

                case 'd':
                    d = kum->is_pressed();
                break;

                // Use 'q' to reset Zero's position
                case 'q':
                    if (kum->is_pressed());
                    {
                        set_x_pixel_position(0);
                        set_y_pixel_position(-10);
                    }
                break;

            }
        }
        break;
    }
}

void Zero::add_collide_object(shared_ptr<Sprite> c)
{
    collide_objects.push_back(c);
}
