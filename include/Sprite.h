#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Frame.h"
#include "Pixel.h"

#include <chrono>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Sprite
{
    protected:

    // Position on screen relative to origin
    // TODO: Top 32 bits are pixel position, bottom 32 bits are sub-pixel position
    // This allows for positions and speeds that aren't tied to frame rate
    long int x_position;
    long int y_position;
    long int z_position;
        
    // Size of sprite
    unsigned long int width;
    unsigned long int height;
    unsigned long int depth;
    
    // Each element of the dict is 3D model of what this particular sprite
    // should look like at this distance from the camera, taking zoom into
    // account. The engine will determine based on the camera's relative
    // z position and zoom level, how big the sprite should appear on screen,
    // and look for the appropriate model in the following dict.
    //map<long int, Model> models;
    
    // Time at which the last frame was animated in milliseconds since UNIX epoch
    long long last_run_time;
    
    // Character that denotes that the given 'pixel' should not be drawn
    char alpha_char = ' ';
    
    // Current frame as it should be displayed
    // Must be defined everytime animate() is called
    Frame current_frame = Frame(0, 0);
    
    unsigned int current_frame_index = 0;
    
    // Place to store useful frames
    vector<Frame> frames;
    
    // Let the engine decide the color of this sprite based on light sources
    bool respect_light_sources = false;
    
    // Whether or not engine looks at normal to determine light brightness
    // Only applies if respect_light_sources is true
    bool use_normal_mapping = false;
    
    // If this sprite is entirely off screen, this determines if the animate() function is called
    bool animate_off_screen = false;
    
    
    public:
    
        // Sprites that this sprite is made out of
        // Any transformation/translation of this sprite will be done to sub_sprites
        vector<Sprite*> sub_sprites;
    
        Sprite();
        
        Sprite(long int, long int, long int);
        
        ~Sprite();
        
        Pixel* get_pixel(long int, long int);
        
        long int get_height();
        
        long int get_width();
        
        long int get_x_position();
        
        long int get_y_position();
        
        long int get_z_position();
        
        bool respects_light_sources();
        
        bool compare_normals();
        
        void set_frame_chars(vector<string>);
    
        // Moving to Frame
        //void map_sprite(char, Sprite*, long int, long int);
        
        void move(long int, long int, long int);
        
        virtual void animate();
    
};

#endif
