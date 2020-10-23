// This file is a proof of concept for Taeto

using namespace std;

#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <chrono>

int w_char = 119;
int a_char = 97;
int s_char = 115;
int d_char = 100;
int space_char = 32;


class Distortion_Map
{
    
};


class Texture
{
    public:
    
        Texture();
    
        void shift(int, int);
};


// Which direction the texture will shift
void Texture::shift(int x_shift, int y_shift)
{

}


class Model
{
    public:
    
        Model();
        
};

Model::Model(void)
{

}


// Sprites are made up of models and/or other sprites
class Sprite
{
    protected:

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
    
    // Local timer
    // Used to determine when next frame should be generated
    time_t local_timer;
    
    // Character that denotes that the given 'pixel' should not be drawn
    char alpha_char = '\0';
    
    // Current frame as it should be displayed
    //vector<string> current_frame;
    
    // Because fuck C strings
    vector<string> data;
    
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
        
        void animate();
    
};


Sprite::Sprite(void)
{
    local_timer = 0;
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
// First parameter is time since last frame was generated
// void Sprite::animate(time_t time_diff)
void Sprite::animate()
{
    // Add time_diff to local counter
    // Keeps sprite from updating frame too fast, and allows
    // sprites to be animated at different speeds
    //local_timer += time_diff;
    
    // Animate if enough time has passed
    time_t frame_length;
    // if (time_diff / frame_length > 0)
    // {
    //     // animate
    // }
    
    //current_frame = data;
}


class Engine
{
    // Sprites to render
    vector<Sprite> sprites;
    
    // Frame rate
    unsigned int frame_rate = 0;
    
    // Camera position
    long int x_camera_position;
    long int y_camera_position;
    long int z_camera_position;
    
    public:
    
        Engine(void);
        
        void add_sprite(Sprite);
                
        void animate();
        
        void display_frame(vector<string>);
    
        void move_camera(long int, long int, long int);
        
        vector<string> render_frame();
        
        void write_frame(char*);
        
};


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
    
    // Initialize camera position
    x_camera_position = 0;
    y_camera_position = 0;
    z_camera_position = 0;
    
}


void Engine::add_sprite(Sprite sprite)
{

    sprites.push_back(sprite);

}


void Engine::animate()
{

    // Loop over every sprite 
    vector<Sprite>::iterator sprite;
    for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)

        // Tell each sprite to animate itself
        // It is each sprite's job to animate it's own sub-sprites
        sprite->animate();

}


void Engine::display_frame(vector<string> frame)
{

    // Loop over lines
    for (int i = 0; i < frame.size(); i++)
    {
    
        // Loop over columns
        for (int j = 0; j < frame[i].length(); j++)
        {
        
            // Get pixel in question
            char pixel = frame[i][j];
        
            // Move cursor to origin
            move(i, j);

            // Write character
            waddch(stdscr, pixel);
        
            // Refresh window
            wrefresh(stdscr);
            
        }
        
    }

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
            vector<Sprite>::iterator sprite;
            for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)
            {
                // Get pixel relative to sprite
                long int rel_x = abs_x - sprite->get_x_position();
                long int rel_y = abs_y - sprite->get_y_position();
                
                // Get sprite dimensions
                long int sprite_width = sprite->get_width();
                long int sprite_height = sprite->get_height();
                
                // If pixel overlaps with sprite
                if ( 0 <= rel_x && rel_x < sprite_width && 0 <= rel_y && rel_y < sprite_height)
                     
                    // First check if sprite cares about 'pixel'
                    if (sprite->get_pixel(rel_x, rel_y) != '\0')
                
                        // Write 'pixel' to frame
                        frame_pixel = sprite->get_pixel(rel_x, rel_y);

            }
            
            // Write pixel to line
            line += frame_pixel;
        }
        
        // Add to frame
        frame.push_back(line);
    }
    
    return frame;

}





class Palm_tree: public Sprite
{
public:
    // I am going to kill myself
    Palm_tree() { height = 22; 
                width = 45;
                x_position = 0;
                y_position = 0;
                current_frame = {"              _____                          ",
                "           __/ / / \\_                        ",
                "          / / / / / /\\                       ",
                "          \\/\\/\\/ / / /\\                      ",
                "               \\/\\/_/ /\\                     ",
                "          ________  \\/ /|     ________       ",
                "     ____/ / / / /\\__\\/ | ___/_ \\ \\ \\ \\__    ",
                "  __/ / / / / / / / /\\|/|/ \\ \\ \\_\\ \\ \\ \\ \\   ",
                " / / / / / / / / / / / \\/ \\ \\ \\ \\ \\_\\_\\ \\ \\  ",
                "/ / / / /\\/\\/\\/\\/\\/\\/\\|XX|/\\ \\ \\ \\ \\   \\_\\ \\ ",
                "|/\\/\\/\\/              |XX|  \\/\\ \\ \\ \\     \\ |",
                "                      |XX|     \\/\\ \\|      \\|",
                "                      \\XX\\        \\ |        ",
                "                       |XX|        \\|        ",
                "                       |XX|                  ",
                "                       \\XX\\                  ",
                "                        |XX|                 ",
                "                        |XX|                 ",
                "                        \\XX\\                 ",
                "                         |XX\\                ",
                "                        /XXXX\\               ",
                "                       /XXXXXX\\              "};}
                //data[3][2] = 'l';}
};


int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}


int main()
{
    Engine engine;
    
    Palm_tree tree;
    
    engine.add_sprite(tree);

    chrono::microseconds time;
   
    move(0, 0);
    string s = "Testing, attention please.          ";
    waddstr(stdscr, s.c_str());
        
    // Refresh window
    wrefresh(stdscr);
    
    sleep(2);
 
    while (TRUE)
    {
        int c = getch();
        switch(c)
        {
            case 'w':
                engine.move_camera(0, -1, 0);
                break;
            
            case 'a':
                engine.move_camera(-1, 0, 0);
                break;
                
            case 's':
                engine.move_camera(0, 1, 0);
                break;
                
            case 'd':
                engine.move_camera(1, 0, 0);
                break;
        }
    
        // Tell every sprite to animate itself
        engine.animate();
        
        // Render new frame
        vector<string> new_frame = engine.render_frame();
        
        // Display new frame
        engine.display_frame(new_frame);
        
        // Wait for the length of one frame
        // Test with 1FPS
        usleep(100000);
    }

}
