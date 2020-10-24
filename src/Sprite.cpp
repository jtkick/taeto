#include "Sprite.h"

Sprite::Sprite(void)
{
    last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

char Sprite::get_pixel(long int rel_x, long int rel_y)
{
    if (current_frame[rel_y][rel_x] != alpha_char)
        return current_frame[rel_y][rel_x];
    else
        return '\0';
}

long int Sprite::get_x_position()
{
    return x_position;
}
        
long int Sprite::get_y_position()
{
    return y_position;
}
        
long int Sprite::get_width()
{
    return width;
}
        
long int Sprite::get_height()
{
    return height;
}

// Maps a sub-sprite on this sprite using map
void Sprite::map(char c, Texture tex)
{

}

// Move sprite in space
void Sprite::move(long int x_diff, long int y_diff, long int z_diff)
{

    // Move self
    x_position += x_diff;
    y_position += y_diff;
    z_position += z_diff;
    
    // Move all sub_sprites
    vector<Sprite>::iterator it;
    int i = 0;
    for (it = sub_sprites.begin(); it != sub_sprites.end(); it++, i++)
        it->move(x_diff, y_diff, z_diff);
        
}

// Generate new frame of sprite
// MUST be implemented by derived classes
void Sprite::animate()
{

}
