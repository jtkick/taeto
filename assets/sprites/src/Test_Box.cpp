#include "Test_Box.h"

Test_Box::Test_Box(Color c)
{
    height = 8;
    width = 16;

    x_position = 0;
    y_position = 0;
    z_position = 0;

    current_frame = Frame(height, width);

    collide = true;

    set_color(c);

    respect_light_sources = true;

}

void Test_Box::set_color(Color c)
{
    vector<vector<Color>> color_vector;

    // Dull color
    Color dc = Color(c.get_red() / 2, c.get_green() / 2, c.get_blue() / 2);

    for (int y = 0; y < height; y++)
    {
        vector<Color> row;
        for (int x = 0; x < width; x++)
        {
            if ( (x % 8 < 4) != (y % 4 < 2) )
            {
                row.push_back(c);
            }
            else
            {
                row.push_back(dc);
            }
        }
        color_vector.push_back(row);
    }

    current_frame.set_background_colors(color_vector);
}

void Test_Box::handle_collision(shared_ptr<Sprite> other_sprite)
{
    /*
    uint64_t original_x = other_sprite->get_x_pixel_position();
    uint64_t original_y = other_sprite->get_y_pixel_position();
    uint64_t original_z = other_sprite->get_z_pixel_position();

    uint64_t x_diff = 0;
    uint64_t y_diff = 0;
    uint64_t z_diff = 0;

    // Move other sprite based on relative speed
    double rel_x_speed = other_sprite->get_x_speed() - this->get_x_speed();
    if (rel_x_speed >= 0)
    {
        // Null x speed
        this->set_x_speed(0.0);

        // Move other_sprite left
        while (this->collides_with(other_sprite))
            other_sprite->set_y_pixel_position(other_sprite->get_x_pixel_position() - 1);
    }
    else
    {
        // Null x speed
        this->set_x_speed(0.0);

        // Move other_sprite left
        while (this->collides_with(other_sprite))
            other_sprite->set_y_pixel_position(other_sprite->get_x_pixel_position() - 1);
    }

    // Save x diff
    x_diff = other_sprite->get_x_pixel_position() - original_x;

    // Put back to original position
    other_sprite->set_x_pixel_position(original_x);

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
    */
}
