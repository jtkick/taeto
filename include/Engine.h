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
    
    // If set to true, engine will display FPS in top left corner
    bool display_frame_rate;
    
    public:
    
        Engine(void);
        
        ~Engine(void);
        
        void add_sprite(Sprite*);
                
        void animate();
        
        void display_frame(Frame);
    
        void move_camera(long int, long int, long int);
        
        Frame render_frame();
        
};

#endif
