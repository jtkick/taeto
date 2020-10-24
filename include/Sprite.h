#ifndef SPRITE_H
#define SPRITE_H

#include "Model.h"
#include "Texture.h"

#include <chrono>
#include <string>
#include <vector>

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
    
    // models is an array of 3d models at different zoom levels
    //vector<Model> models;
    Model model;
        
    // Sprites that this sprite is made out of
    // Any transformation/translation of this sprite will be done to sub_sprites
    vector<Sprite> sub_sprites;
    
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
        vector<string> current_frame;
    
        Sprite();
        
        char get_pixel(long int, long int);
        
        long int get_height();
        
        long int get_width();
        
        long int get_x_position();
        
        long int get_y_position();
    
        void map(char, Texture);
        
        void move(long int, long int, long int);
        
        virtual void animate();
    
};

#endif
