// This file is a proof of concept for Taeto

using namespace std;

#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <ctime>

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


// Sprites are made up of models and/or other sprites
class Sprite
{

    // Position on screen relative to origin? parent sprite?
    long int x_position;
    long int y_position;
    long int z_position;
        
    // Size of sprite
    long int height;
    long int width;
    long int depth;
    
    // models is an array of 3d models at different zoom levels
    vector<Model> models;
        
    // Sprites that this sprite is made out of
    // Any transformation/translation of this sprite will be done to sub_sprites
    vector<Sprite> sub_sprites;
    
    // Local timer
    // Used to determine when next frame should be generated
    time_t local_timer;
    
    public:
    
        Sprite();
        
        char get_pixel(long int, long int);
    
        void map(char, Texture);
        
        void move(long int, long int, long int);
        
        void animate(time_t);
    
};


Sprite::Sprite(void)
{
    local_timer = 0;
}


char Sprite::get_pixel(long int abs_x, long int abs_y)
{
    return '\0';
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
    {
        (*it).move(x_diff, y_diff, z_diff);
    } 
}


// Generate new frame of sprite
// First parameter is time since last frame was generated
void Sprite::animate(time_t time_diff)
{
    // Add time_diff to local counter
    // Keeps sprite from updating frame too fast, and allows
    // sprites to be animated at different speeds
    local_timer += time_diff;
    
    // Animate if enough time has passed
    time_t frame_length;
    // if (time_diff / frame_length > 0)
    // {
    //     // animate
    // }
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
    
        void move_camera(long int, long int, long int);
        
        void render_frame();
        
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
    
}


void Engine::move_camera(long int x_diff, long int y_diff, long int z_diff)
{

    // Update camera position
    x_camera_position += x_diff;
    y_camera_position += y_diff;
    z_camera_position += z_diff;
    
}


void Engine::render_frame()
{
    // Create frame for window
    int h, w;
    getmaxyx(stdscr, h, w);

    // Loop over each 'pixel' in frame
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            // Get absolute location of given 'pixel'
            long int abs_x = x_camera_position - (w / 2) + x;
            long int abs_y = y_camera_position - (h / 2) + x;
            
            // Loop over each sprite, and write to current frame
            vector<Sprite>::iterator it;
            int i = 0;
            for (it = sprites.begin(); it != sprites.end(); it++, i++)
            {
                // First check if given 'pixel' overlaps with window
        
            }
        }
    } 
}




/*
class Palm_tree: public Sprite
{
public:
int h;
int w;
const char *data;
    // I am going to kill myself
    Palm_tree() :
           h(22),
           w(45),
           data("              _____                          "
                "           __/ / / \\_                        "
                "          / / / / / /\\                       "
                "          \\/\\/\\/ / / /\\                      "
                "               \\/\\/_/ /\\                     "
                "          ________  \\/ /|     ________       "
                "     ____/ / / / /\\__\\/ | ___/_ \\ \\ \\ \\__    "
                "  __/ / / / / / / / /\\|/|/ \\ \\ \\_\\ \\ \\ \\ \\   "
                " / / / / / / / / / / / \\/ \\ \\ \\ \\ \\_\\_\\ \\ \\  "
                "/ / / / /\\/\\/\\/\\/\\/\\/\\|XX|/\\ \\ \\ \\ \\   \\_\\ \\ "
                "|/\\/\\/\\/              |XX|  \\/\\ \\ \\ \\     \\ |"
                "                      |XX|     \\/\\ \\|      \\|"
                "                      \\XX\\        \\ |        "
                "                       |XX|        \\|        "
                "                       |XX|                  "
                "                       \\XX\\                  "
                "                        |XX|                 "
                "                        |XX|                 "
                "                        \\XX\\                 "
                "                         |XX\\                "
                "                        /XXXX\\               "
                "                       /XXXXXX\\              ") {}
};
*/

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

/*
Palm_tree tree;

for( int i = 0; i < tree.h; i++)
{
    for (int j = 0; j < tree.w; j++)
    {
    

    cout << tree.data[i * tree.w + j];
    }
    cout << endl;
    }
*/
return 0;


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
    
    // Get window dimensions
    int h, w;
    getmaxyx(stdscr, h, w);

    int x = 10;
    int y = 10;
    
    float y_speed = 0;
    
    move(5, 50);
    wrefresh(stdscr);
    
    while (true)
    {
        if (kbhit())
        {
        
            //clear();
            wrefresh(stdscr);
         
            // Get character input
            int ch = getch();
            
            move(0, 0);
            string s = "C: " + to_string(ch);
            waddstr(stdscr, s.c_str());
            
            move(y, x);
            addch(' ');
            
            // Move character
            switch (ch)
            {
                case 119:
                    y = (y - 1) % h;
                    break;
                    
                case 97:
                    x = (x - 1) % w;
                    break;
                    
                case 115:
                    y = (y + 1) % h;
                    break;
                    
                case 100:
                    x = (x + 1) % w;
                    break;
            }
            
            move(1, 0);
            s = "X: " + to_string(x);
            waddstr(stdscr, s.c_str());
            
            move(2, 0);
            s = "Y: " + to_string(y);
            waddstr(stdscr, s.c_str());
            
            if (ch == space_char)
            {
                y_speed = 1.0;
                for (int i = -3; i < 5; i++)
                {
                    clearok(stdscr, TRUE);

                    usleep(100000);
                    y -= (-0.1 * pow(i, 3));
                    
                    move(0, 0);
                    string s = "Y: " + to_string(y) + "          ";
                    waddstr(stdscr, s.c_str());
                    
                    move(1, 0);
                    s = "i: " + to_string(i) + "          ";
                    waddstr(stdscr, s.c_str());
                    
                    // Move cursor to origin
                    move((int)y, x);

                    // Write character
                    waddch(stdscr, 'o');
        
                    // Refresh window
                    wrefresh(stdscr);
                    
                }
            }
        
            // Move cursor to origin
            move(y, x);

            // Write character
            waddch(stdscr, 'o');
            
            move(h, w);

            // Refresh window
            wrefresh(stdscr);
            
            usleep(4166);
        }
        
    }

}
