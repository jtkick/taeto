#include "Sprite.h"

Sprite::Sprite(void)
{
    last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    //current_frame = Frame(0, 0);

    x_position = 0;
    y_position = 0;
    z_position = 0;

    x_force = 0.0;
    y_force = 0.0;
    z_force = 0.0;

    x_speed = 0.0;
    y_speed = 0.0;
    z_speed = 0.0;

    mass = 1.0;

    time_physics_last_applied = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
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

int32_t Sprite::get_x_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((x_position >> 32) & 0x00000000FFFFFFFF);
}

int32_t Sprite::get_y_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((y_position >> 32) & 0x00000000FFFFFFFF);
}

int32_t Sprite::get_z_pixel_position()
{
    // Top 32 bits are pixel position
    return (int32_t)((z_position >> 32) & 0x00000000FFFFFFFF);
}

int64_t Sprite::get_x_exact_position()
{
    return x_position;
}

int64_t Sprite::get_y_exact_position()
{
    return y_position;
}

int64_t Sprite::get_z_exact_position()
{
    return z_position;
}

double Sprite::get_x_force()
{
    return x_force;
}

double Sprite::get_y_force()
{
    return y_force;
}

double Sprite::get_z_force()
{
    return z_force;
}

double Sprite::get_x_speed()
{
    return x_speed;
}

double Sprite::get_y_speed()
{
    return y_speed;
}

double Sprite::get_z_speed()
{
    return z_speed;
}

double Sprite::get_mass()
{
    return mass;
}

long long Sprite::get_time_physics_last_applied()
{
    return time_physics_last_applied;
}

bool Sprite::is_visible()
{
    return visible;
}

bool Sprite::get_collide()
{
    return collide;
}

bool Sprite::get_detect_collisions()
{
    return detect_collisions;
}

bool Sprite::respects_light_sources()
{
    return respect_light_sources;
}

bool Sprite::compare_normals()
{
    return use_normal_mapping;
}

int64_t Sprite::get_width()
{
    return width;
}

int64_t Sprite::get_height()
{
    return height;
}

void Sprite::set_x_pixel_position(int32_t x)
{
    x_position = (int64_t)(x) << 32;
}

void Sprite::set_y_pixel_position(int32_t y)
{
    y_position = (int64_t)(y) << 32;
}

void Sprite::set_z_pixel_position(int32_t z)
{
    z_position = (int64_t)(z) << 32;
}

void Sprite::set_x_exact_position(int64_t x)
{
    x_position = x;
}

void Sprite::set_y_exact_position(int64_t y)
{
    y_position = y;
}

void Sprite::set_z_exact_position(int64_t z)
{
    z_position = z;
}

void Sprite::set_x_speed(double x)
{
    x_speed = x;
}

void Sprite::set_y_speed(double y)
{
    y_speed = y;
}

void Sprite::set_z_speed(double z)
{
    z_speed = z;
}

void Sprite::set_mass(double m)
{
    mass = m;
}

void Sprite::set_time_physics_last_applied(long long t)
{
    time_physics_last_applied = t;
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


// Detect collisions with other sprite
bool Sprite::collides_with(shared_ptr<Sprite> sprite_ptr)
{
    // Do rough collision detection
    // x locations don't overlap
    if ((this->get_x_pixel_position() > sprite_ptr->get_x_pixel_position() + sprite_ptr->get_width() - 1) ||
        (this->get_x_pixel_position() + this->get_width() - 1 < sprite_ptr->get_x_pixel_position()))
        return false;

    // y locations don't overlap
    if (this->get_y_pixel_position() > sprite_ptr->get_y_pixel_position() + sprite_ptr->get_height() - 1 ||
        this->get_y_pixel_position() + this->get_height() - 1 < sprite_ptr->get_y_pixel_position())
        return false;

    // Different z-plane
    if (this->get_z_pixel_position() != sprite_ptr->get_z_pixel_position())
        return false;

    // Now it's guaranteed that the sprites overlap in some way, so loop over each sprite's
    // collision mesh and compare to the other

    return true;
}

void Sprite::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    throw "lmao";
}

// Move sprite in space
void Sprite::move(long int x_diff, long int y_diff, long int z_diff)
{

    // Move self
    x_position += (long long)(x_diff) << 32;
    y_position += (long long)(y_diff) << 32;
    z_position += (long long)(z_diff) << 32;

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
