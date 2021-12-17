#include "Sprite.h"

////////////////////////////////////////////////////////////////////////
///                           CONSTRUCTORS                           ///
////////////////////////////////////////////////////////////////////////

Sprite::Sprite(void)
{
    // Set all default values
    x_position = 0;
    y_position = 0;
    z_position = 0;

    width = 0;
    height = 0;

    scaling_factor = 1.0;

    z_speed = 0.0;
    y_speed = 0.0;
    x_speed = 0.0;

    x_force = 0.0;
    y_force = 0.0;
    z_force = 0.0;

    mass = 1.0;

    collide = false;

    detect_collisions = false;

    respect_light_sources = false;

    use_normal_mapping = false;

    animate_off_screen = false;

    time_physics_last_applied = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    visible = false;
}

Sprite::Sprite(long int x, long int y, long int z)
{
    // Set initial position
    x_position = x;
    y_position = y;
    z_position = z;
}

////////////////////////////////////////////////////////////////////////
///                            DESTRUCTOR                            ///
////////////////////////////////////////////////////////////////////////

Sprite::~Sprite(void)
{

}

////////////////////////////////////////////////////////////////////////
///                             GETTERS                              ///
////////////////////////////////////////////////////////////////////////

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

int64_t Sprite::get_height()
{
    return height;
}

int64_t Sprite::get_width()
{
    return width;
}

double Sprite::get_scaling_factor()
{
    return scaling_factor;
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

double Sprite::get_mass()
{
    return mass;
}

uint64_t Sprite::get_tags()
{
    return tags;
}

bool Sprite::get_collide()
{
    return collide;
}

bool Sprite::get_detect_collisions()
{
    return detect_collisions;
}

bool Sprite::get_respect_light_sources()
{
    return respect_light_sources;
}

bool Sprite::get_use_normal_mapping()
{
    return use_normal_mapping;
}

bool Sprite::get_animate_off_screen()
{
    return animate_off_screen;
}

long long Sprite::get_time_physics_last_applied()
{
    return time_physics_last_applied;
}

bool Sprite::get_visible()
{
    return visible;
}

////////////////////////////////////////////////////////////////////////
///                             SETTERS                              ///
////////////////////////////////////////////////////////////////////////

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

void Sprite::set_scaling_factor(double sf)
{
    scaling_factor = sf;
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

void Sprite::set_x_force(double x)
{
    x_force = x;
}

void Sprite::set_y_force(double y)
{
    y_force = y;
}

void Sprite::set_z_force(double z)
{
    z_force = z;
}

void Sprite::set_mass(double m)
{
    mass = m;
}

void Sprite::set_tags(uint64_t t)
{
    tags = t;
}

void Sprite::set_collide(bool c)
{
    collide = c;
}

void Sprite::set_detect_collisions(bool dc)
{
    detect_collisions = dc;
}

void Sprite::set_respect_light_sources(bool rls)
{
    respect_light_sources = rls;
}

void Sprite::set_use_normal_mapping(bool unm)
{
    use_normal_mapping = unm;
}

void Sprite::set_animate_off_screen(bool aos)
{
    animate_off_screen = aos;
}

void Sprite::set_time_physics_last_applied(long long tpla)
{
    time_physics_last_applied = tpla;
}

void Sprite::set_visible(bool v)
{
    visible = v;
}

////////////////////////////////////////////////////////////////////////
///                         HELPER METHODS                           ///
////////////////////////////////////////////////////////////////////////

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

void Sprite::serialize(std::filesystem::path filename, bool overwrite=false)
{
    // Create and open file
    if (!overwrite)
    {
        if (std::filesystem::exists(filename))
        {
            throw "Kill yourself.";
        }
    }
    std::ofstream file(filename);

    // Loop over each frame
    int i = 0;
    for (auto it = frames.begin(); it != frames.end(); it++)
    {
        // Open map element
        file << "{";

        // Output frame name
        file << "\"" << it->first << "\",";

        // Add serialized frame
        file << it->second.serialize();

        // Close map element
        file << "}";

        // If not last frame, output comma
        if (i++ != frames.size() - 1)
        {
            file << ",";
        }
        file << "\n";
    }
}

Pixel& Sprite::get_pixel(long int rel_y, long int rel_x)
{
    return current_frame.get_pixel(rel_y, rel_x);
    //return get_current_frame()->get_pixel((long int)(rel_y),// / scaling_factor),
    //                                      (long int)(rel_x ));/// scaling_factor));
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

void Sprite::save(std::filesystem::path directory)
{
    // Make sure directory exists
    if (std::filesystem::is_directory(directory))
    {
        // Make sure directory is empty
        if (!std::filesystem::is_empty(directory))
        {
            throw "gtfo";
        }
    }
    else
    {
        std::filesystem::create_directory(directory);
    }

    // Now that directory exists and is sure to be empty, start formatting and populating it
    // Start with descriptor file
    ofstream desc_file;
    desc_file.open(directory.u8string() + "/description.txt");
    if (desc_file)
    {
        desc_file << "version=1";
        desc_file << "height=" + std::to_string(height);
        desc_file << "width=" + std::to_string(width);
        desc_file << "scaling_factor=" + std::to_string(scaling_factor);
        desc_file << "mass=" + std::to_string(mass);
        desc_file << "collide=" + std::to_string(collide);
        desc_file << "detect_collisions=" + std::to_string(detect_collisions);
        desc_file << "respect_light_sources=" + std::to_string(respect_light_sources);
        desc_file << "use_normal_mapping=" + std::to_string(use_normal_mapping);
        desc_file << "animate_off_screen=" + std::to_string(animate_off_screen);
    }
    else
    {
        throw "Don't make me kill myself.";
    }

    // Now export frames
    for (auto const& frame: std::filesystem::directory_iterator{directory})
    {
        std::filesystem::path frame_dir = directory / frame;

        // Create frame object
        //std::unique_ptr<Frame> new_frame = std::make_unique<Frame>;


    }

}

////////////////////////////////////////////////////////////////////////
///                       CHILD SPRITE METHODS                       ///
////////////////////////////////////////////////////////////////////////

void Sprite::animate()
{

}

shared_ptr<Frame> Sprite::get_current_frame()
{

}

void Sprite::handle_collision(shared_ptr<Sprite> sprite_ptr)
{

}
