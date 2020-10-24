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

    sprites.push_back(sprite);

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

void Engine::display_frame(vector<string> frame)
{

    // Loop over lines
    for (int i = 0; i < frame.size(); i++)
    {
    
        //move(i, 0);
        //waddstr(stdscr, frame[i].c_str());
            
        // Loop over columns
        for (int j = 0; j < frame[i].length(); j++)
        {
        
            // Get pixel in question
            char pixel = frame[i][j];
        
            // Move cursor to origin
            move(i, j);

            // Write character
            waddch(stdscr, pixel);
            
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

vector<string> Engine::render_frame()
{
    // Create frame for window
    int h, w;
    getmaxyx(stdscr, h, w);
    
    vector<string> frame;

    // Loop over each 'pixel' in frame
    for (int y = 0; y < h; y++)
    {
        // Create row
        string line;
        
        for (int x = 0; x < w; x++)
        {
            // 'Pixel' to be added to new frame
            char frame_pixel = ' ';
        
            // Get absolute location of given 'pixel'
            long int abs_x = x_camera_position - (w / 2) + x;
            long int abs_y = y_camera_position - (h / 2) + y;
            
            // Loop over each sprite, and write to current frame
            vector<Sprite*>::iterator sprite;
            for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)
            {
                // Get pixel relative to sprite
                long int rel_x = abs_x - (*sprite)->get_x_position();
                long int rel_y = abs_y - (*sprite)->get_y_position();
                
                // Get sprite dimensions
                long int sprite_width = (*sprite)->get_width();
                long int sprite_height = (*sprite)->get_height();
                
                // If pixel overlaps with sprite
                if ( 0 <= rel_x && rel_x < sprite_width && 0 <= rel_y && rel_y < sprite_height)
                     
                    // First check if sprite cares about 'pixel'
                    if ((*sprite)->get_pixel(rel_x, rel_y) != '\0')
                
                        // Write 'pixel' to frame
                        frame_pixel = (*sprite)->get_pixel(rel_x, rel_y);

            }
            
            // Write pixel to line
            line += frame_pixel;
        }
        
        // Add to frame
        frame.push_back(line);
    }
    
    return frame;

}
