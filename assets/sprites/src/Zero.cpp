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
    //y_force = 200000000000;

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

    current_frame = f;

    respect_light_sources = false;
}

void Zero::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    // Null y speed
    this->set_y_speed(0.0);

    // Move up
    while (this->collides_with(sprite_ptr))
        this->set_y_pixel_position(this->get_y_pixel_position() - 1);
}

void Zero::add_collide_object(shared_ptr<Sprite> c)
{
    collide_objects.push_back(c);
}
