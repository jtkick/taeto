#include "Sprite.h"


#include <iostream>

Sprite::Sprite(void)
{
    last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    //current_frame = Frame(0, 0);

    height = 0;
    width = 0;
}

Sprite::Sprite(unsigned long int h, unsigned long int w)
{
    height = h;
    width = w;
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

Pixel* Sprite::get_pixel(long int rel_x, long int rel_y)
{
    // Empty pixel with c == '\0'
    //Pixel p;

    return current_frame.get_pixel(rel_y, rel_x);

    // If pixel is out of bounds, this sprite doesn't care about given frame location
    if (rel_x < 0 || rel_x >= current_frame.get_width())
        return NULL;
    if (rel_y < 0 || rel_y >= current_frame.get_height())
        return NULL;

    // If pixel does overlap with given coordinate, make sure character is not meant to be transparent
    if (current_frame.get_pixel(rel_y, rel_x)->get_char() != alpha_char)
        return current_frame.get_pixel(rel_y, rel_x);

    // TODO: THIS LINE SHOULD NEVER BE REACHED, LIKELY WORSENING EFFICIENCY
    else
        return NULL;

    //throw "ouch";
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

bool Sprite::respects_light_sources()
{
    return respect_light_sources;
}

bool Sprite::compare_normals()
{
    return use_normal_mapping;
}

Frame* Sprite::get_frame(string name)
{
    return &(frames.find(name)->second);
}

long int Sprite::get_height()
{
    return height;
}

long int Sprite::get_width()
{
    return width;
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


///////////////////////////////////////////////////////////////////////
///                        DESIGN METHODS                           ///
///////////////////////////////////////////////////////////////////////

void Sprite::add_frame(string name)
{
    frames.insert(std::pair<string, Frame>(name, Frame(height, width)));
}

void Sprite::print_frames()
{
    std::cout << "Frame names:";
    for (std::map<string, Frame>::iterator it = frames.begin(); it != frames.end(); it++)
        std::cout << "\t" << it->first << std::endl;
    std::cout << std::endl;
}

void Sprite::remove_frame(string name)
{
    frames.erase(name);
}

void Sprite::rename_frame(string old_name, string new_name)
{
    std::map<string, Frame>::iterator it = frames.find(old_name);
    if (it != frames.end())
    {
        std::cout << "it->first" << it->first << std::endl;
        //std::cout << "it->second" << it->second << std::endl;
        frames.emplace(new_name, it->second);
        frames.erase(it);
    }
    else
    {
        throw "Frame not in sprite.";
    }
}

void Sprite::resize(unsigned long int h, unsigned long int w)
{
    // Set dimensions
    height = h;
    width = w;

    // Apply dimensions to all frames
    std::map<string, Frame>::iterator it;
    for (it = frames.begin(); it != frames.end(); it++)
        (it->second).resize(height, width);
}
