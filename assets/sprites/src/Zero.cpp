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
}

void Zero::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    // Handle floor collision
    if ((sprite_ptr->get_tags() & FLOOR_TAG) == FLOOR_TAG)
    {
        // Null y speed
        this->set_y_speed(0.0);

        // Slow x speed
        //this->set_x_speed(this->get_x_speed() * 0.5);

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

void Zero::add_collide_object(shared_ptr<Sprite> c)
{
    collide_objects.push_back(c);
}
