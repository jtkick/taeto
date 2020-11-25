#include "Engine.h"
#include "Sprite.h"

#include <vector>

Engine::Engine()
{
    // Initialize data members
    frame_rate = 0;
    
    // Initialize ncurses
    initscr();
    
    // Don't buffer input characters
    cbreak();
    
    // Don't print entered characters
    noecho();
    
    // Allow special keystrokes
    keypad(stdscr, TRUE);
    
    nodelay(stdscr, TRUE);
    
    scrollok(stdscr, TRUE);
    
    // Don't show the cursor
    curs_set(0);
    
    // Initialize camera position
    x_camera_position = 0;
    y_camera_position = 0;
    z_camera_position = 0;
    
}

void Engine::add_sprite(Sprite* sprite)
{
    // Add sprite to list
    sprites.push_back(sprite);
    
    // Loop over every sub_sprite
    // Engine does not care about actual sprite structures, so just add every
    // individual sprite to the list to be rendered
    // TODO: YEAH THATS NOT GONNA WORK
    vector<Sprite*>::iterator sub_sprite;
    for (sub_sprite = sprite->sub_sprites.begin(); sub_sprite != sprite->sub_sprites.end(); sub_sprite++)
    
        // Recursively add sub_sprite to list
        this->add_sprite(*sub_sprite);

}

void Engine::animate()
{

    // Loop over every sprite 
    vector<Sprite*>::iterator sprite;
    for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)

        // Tell each sprite to animate itself
        // It is each sprite's job to animate it's own sub-sprites
        (*sprite)->animate();

}

void Engine::display_frame(Frame f)
{

    start_color();
    
    //init_pair(1, COLOR_RED, COLOR_BLACK);
    //init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Loop over rows
    for (int h = 0; h < f.get_height(); h++)
    {
    
        //move(i, 0);
        //waddstr(stdscr, frame[i].c_str());
            
        // Loop over columns
        for (int w = 0; w < f.get_width(); w++)
        {
        
            // Get pixel in question
            char c = f.get_pixel(h, w).c;
        
            // Move cursor to origin
            move(h, w);
            
            //if (j % 2 == 0)
            //    attron(COLOR_PAIR(1));
            //else
            //    attron(COLOR_PAIR(2));

            // Write character
            waddch(stdscr, c);
            
        }
        
    }
    
    // Refresh window to show new frame
    wrefresh(stdscr);

}

void Engine::move_camera(long int x_diff, long int y_diff, long int z_diff)
{

    // Update camera position
    x_camera_position += x_diff;
    y_camera_position += y_diff;
    z_camera_position += z_diff;
    
}


//  __________________________
// |     _              _     |
// |   _/ \            / \_   |
// |  |__  \ ________ /  __|  |
// |     \  /        \  /     |
// |      \| ___  ___ |/      |
// |       | \_/  \_/ |       |
// |       (__  /\  __)       |
// |         \\MMMM//         |
// |         /\MMMM/\         |
// |        /  /  \  \        |
// |     __/  /    \  \__     |
// |    |_   /      \   _|    |
// |      \_/        \_/      |
// |                          |
// |  Lasciate ogni speranza, |
// |      voi ch'intrate.     |
// |__________________________|
//

// This method iterates all sprites known to the engine, and renders a
// frame with them.  
Frame Engine::render_frame()
{
    // Create frame for window
    int h, w;
    getmaxyx(stdscr, h, w);
    
    Frame f(h, w);

    // Loop over each 'pixel' in frame
    for (int y = 0; y < h; y++)
    {
        // Create row
        //vector<pixel> line;
        
        for (int x = 0; x < w; x++)
        {
            // 'Pixel' to be added to new frame
            pixel frame_pixel;
            
            // Loop over each sprite, and write to current frame
            vector<Sprite*>::iterator sprite;
            for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)
            {
                // Get distance between sprite and camera
                long int z_diff = z_camera_position - (*sprite)->get_z_position();
                
                // Make sure sprite is at least in front of the camera
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (z_diff <= 0)
                    continue;
            
                // Get absolute position of pixel taking distance from camera into account
                long int abs_x = x_camera_position - (w / 2)*z_diff + (x * z_diff);
                long int abs_y = y_camera_position - (h / 2)*z_diff + (y * z_diff);
                
                // Get pixel relative to sprite
                long int rel_x = abs_x - (*sprite)->get_x_position() * z_diff;
                long int rel_y = abs_y - (*sprite)->get_y_position() * z_diff;
                
                // Get sprite dimensions
                long int sprite_width = (*sprite)->get_width();
                long int sprite_height = (*sprite)->get_height();
                
                // Get index relative to sprite size
                rel_x = (rel_x / z_diff) - 1;
                rel_y = (rel_y / z_diff) - 1;
                
                // If pixel overlaps with sprite
                if ( 0 <= rel_x && rel_x < sprite_width && 0 <= rel_y && rel_y < sprite_height){}
                     
                    // First check if sprite cares about 'pixel'
                    //if (((*sprite)->get_pixel(rel_x, rel_y)).c != '\0')
                
                        // Write 'pixel' to frame
                        //frame_pixel = (*sprite)->get_pixel(rel_x, rel_y);

            }
            
            // Write pixel to line
            f.set_pixel(y, x, frame_pixel);
        }
        
        // Add to frame
        //f.pixels.push_back(line);
    }
    
    return f;

}
