#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Frame.h"
#include "structs.h"

#include <chrono>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Sprite
{
    public:

    // Position on screen relative to origin? parent sprite?
    long int x_position;
    long int y_position;
    long int z_position;
        
    // Size of sprite
    long int height;
    long int width;
    long int depth;
    
    // Each element of the dict is 3D model of what this particular sprite
    // should look like at this distance from the camera, taking zoom into
    // account. The engine will determine based on the camera's relative
    // z position and zoom level, how big the sprite should appear on screen,
    // and look for the appropriate model in the following dict.
    //map<long int, Model> models;
        
    // Sprites that this sprite is made out of
    // Any transformation/translation of this sprite will be done to sub_sprites
    vector<Sprite*> sub_sprites;
    
    // Time at which the last frame was animated in milliseconds since UNIX epoch
    long long last_run_time;
    
    // Character that denotes that the given 'pixel' should not be drawn
    char alpha_char = ' ';
    
    // Current frame as it should be displayed
    //vector<string> current_frame;
    
    unsigned int current_frame_index = 0;
    
    // Because fuck C strings
    vector<vector<string>> data;
    
    public:
        Frame current_frame;
    
        Sprite();
        
        Sprite(long int, long int, long int);
        
        pixel get_pixel(long int, long int);
        
        long int get_height();
        
        long int get_width();
        
        long int get_x_position();
        
        long int get_y_position();
        
        long int get_z_position();
        
        void set_frame_chars(vector<string>);
    
        void map_sprite(char, Sprite*, long int, long int);
        
        void move(long int, long int, long int);
        
        virtual void animate();
    
};

#endif
