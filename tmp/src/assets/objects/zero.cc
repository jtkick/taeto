#include "assets/objects/zero.hpp"

#include <memory>

#include "components/color.hpp"
#include "frames/render_pixel_frame.hpp"
#include "object/object.hpp"

namespace taeto
{

Zero::Zero()
{
    // Default position to the origin
    x_position_ = 0;
    y_position_ = -10;
    z_position_ = 0;

    // Set frame details
    height = 2;
    width = 6;

    mass = 1;
    y_force = 250000000000;

    collide = true;
    detect_collisions = true;

    // Create collision mesh on Zero's body
    taeto::BoolFrame collision_frame_(height, width, false);
    for (int i = 1; i <= 4; ++i)
        collision_frame_.at(1, i) = true;


    //current_frame = new Frame(7, 7);
    taeto::RenderPixelFrame f(height, width);

    taeto::Color w(255, 255, 255);
    taeto::Color g(43, 43, 43);
    taeto::Color a(0, 0, 0, 0);
    taeto::Color y(127, 127, 127, 127);

    f.chars({ R"(@@__@@)",
              R"(@( ')')"});
    f.foreground_colors( { { a, a, w, w, a, a },
                           { a, w, w, w, w, w } } );
    f.background_colors( { { a, a, a, a, a, a },
                           { a, y, y, y, y, a } } );
    frames.insert(std::make_pair("forward", f));

    f.chars({ R"(@@__@@)",
              R"('(' )@)"});
    f.foreground_colors( { { a, a, w, w, a, a },
                           { w, w, w, w, w, a } } );
    f.background_colors( { { a, a, a, a, a, a },
                           { a, y, y, y, y, a } } );
    frames.insert(std::make_pair("backward", f));

    current_frame_ = frames["forward"];

    respect_light_sources = true;
    use_normal_mapping = false;

    jump_timer = DEFAULT_JUMP_TIME;
}

void Zero::handle_collision(std::shared_ptr<taeto::Sprite> sprite_ptr)
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

void Zero::handle_message(std::shared_ptr<taeto::Message> message)
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
                if (jump_timer_ > milliseconds(0))
                {
                    set_y_force(0);
                    set_y_speed(-130000000000);
                }

                // Start counting down timer
                jump_timer_ = (
                    jump_timer_ -
                    (
                        duration_cast<std::chrono::milliseconds>(
                        system_clock::now().time_since_epoch()) -
                        last_animate_call_
                    )
                );
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
            last_animate_call_ = std::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );
        }
        break;

        case KEY_UPDATE:
        {
            //logger->info("TEST SCENE RECEIVED KEY UPDATE");

            std::shared_ptr<taeto::KeyUpdateMessage> kum =
                std::dynamic_pointer_cast<KeyUpdateMessage>(message);

            // Move camera based on key
            switch(kum->get_key())
            {
                case ' ':
                    space_ = kum->is_pressed();
                break;

                case 'w':
                    w_ = kum->is_pressed();
                break;

                case 'a':
                    a_ = kum->is_pressed();
                break;

                case 's':
                    s_ = kum->is_pressed();
                break;

                case 'd':
                    d_ = kum->is_pressed();
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

}   // namespace taeto
