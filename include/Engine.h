#ifndef ENGINE_H
#define ENGINE_H

#include "Sprite.h"

#include <curses.h>
#include <vector>

class Engine
{
    // Sprites to render
    vector<Sprite*> sprites;
    
    // Frame rate
    unsigned int frame_rate = 0;
    
    // Camera position
    long int x_camera_position;
    long int y_camera_position;
    long int z_camera_position;
    
    public:
    
        Engine(void);
        
        void add_sprite(Sprite*);
                
        void animate();
        
        void display_frame(vector<string>);
    
        void move_camera(long int, long int, long int);
        
        vector<string> render_frame();
        
        void write_frame(char*);
        
};

#endif
