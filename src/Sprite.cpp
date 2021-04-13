#include "Sprite.h"

Sprite::Sprite(void)
{
    last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    //current_frame = Frame(0, 0);
}

Sprite::Sprite(long int x, long int y, long int z)
{
    // Init time so call to animate() doesn't try to animate every frame since the UNIX epoch
    last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    // Set initial position
    x_position = x;
    y_position = y;
    z_position = z;

    // Initialize current_frame array to size of sprite
}

// Destructor
Sprite::~Sprite(void)
{
    // Delete dynamic array
    //delete current_frame;
    //current_frame = NULL;
}

shared_ptr<Pixel> Sprite::get_pixel(long int rel_y, long int rel_x)
{
    return current_frame.get_pixel(rel_y, rel_x);
}

long int Sprite::get_x_position()
{
    return x_position;
}

long int Sprite::get_y_position()
{
    return y_position;
}

long int Sprite::get_z_position()
{
    return z_position;
}

bool Sprite::is_visible()
{
    return visible;
}

bool Sprite::respects_light_sources()
{
    return respect_light_sources;
}

bool Sprite::compare_normals()
{
    return use_normal_mapping;
}

long int Sprite::get_width()
{
    return width;
}

long int Sprite::get_height()
{
    return height;
}

void Sprite::set_visible(bool b)
{
    visible = b;
}

// Maps a sub-sprite on this sprite's given character, at the relative coordinates of the given offsets
// Use c='\0' for any 'pixel'
//void Sprite::map_sprite(char c, Sprite* sub_sprite, long int x_offset, long int y_offset)
//{
//
//}

// Move sprite in space
void Sprite::move(long int x_diff, long int y_diff, long int z_diff)
{

    // Move self
    x_position += x_diff;
    y_position += y_diff;
    z_position += z_diff;

    // Move all sub_sprites
    vector<Sprite*>::iterator it;
    int i = 0;
    for (it = sub_sprites.begin(); it != sub_sprites.end(); it++, i++)
        (*it)->move(x_diff, y_diff, z_diff);

}

// Generate new frame of sprite
// To be implemented by derived classes if sprite should animate itself
void Sprite::animate()
{

}
