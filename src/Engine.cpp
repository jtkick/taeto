#include "Engine.h"

// Used for scaling angle from between 0 and pi, to between 0 and 255
#define ANGLE_SCALE (255/3.14159265)

Engine::Engine()
{
    // Initialize data members
    //frame_rate = 0;
    
    
    //NCURSES STUFF
    
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
    
    // CANNOT GO BELOW ONE, IS USED IN DIVISION
    drawing_plane_distance = 5;
    
    display_frame_rate = false;
    
}

Engine::~Engine()
{
    endwin();
}

void Engine::add_light(Light* light)
{
    // Add light to list
    lights.push_back(light);
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

void Engine::display_frame(Frame* f)
{

    Pixel* current_pixel;
    
    for (int h = 0; h < f->get_height(); h++)
    {
        // Move to beginning of line
        printf("%c[%d;%df", 0X1B, h, 0);
        
        for (int w = 0; w < f->get_width(); w++)
        {
            // Get pixel in question
            current_pixel = f->get_pixel(h, w);
            
            // Write background color
            const Color* c = current_pixel->get_background_color();
            printf("\033[48;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());
            
            // Write foreground color
            c = current_pixel->get_foreground_color();
            printf("\033[38;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());
            
            // Write character
            printf("%c", current_pixel->get_char());
        }
        
    }
    
    // Flush output
    fflush(stdout);

}

void Engine::display_frame_ncurses(Frame* f)
{

    start_color();
    
    //init_pair(1, 127, COLOR_BLACK);
    //init_pair(2, 111, COLOR_BLACK);

    //attron(A_BOLD);
    //attron(A_UNDERLINE);

    short pair_number = 0;
    
    Pixel* p;

    // Loop over rows
    for (uint32_t h = 0; h < f->get_height(); h++)
    {
    
        //move(i, 0);
        //waddstr(stdscr, frame[i].c_str());
            
        // Loop over columns
        for (uint32_t w = 0; w < f->get_width(); w++)
        {
        
            // Get pixel in question
            p = f->get_pixel(h, w);
        
            uint8_t foreground_color = (p->get_foreground_color())->to_iterm();
            uint8_t background_color = (p->get_background_color())->to_iterm();
            
            //init_pair(foreground_color, foreground_color, COLOR_BLACK);
            init_pair(foreground_color, foreground_color, background_color);
                
            attron(COLOR_PAIR(foreground_color));

            // Move cursor to origin
            move(h, w);

            // Write character
            waddch(stdscr, p->get_char());
            
            pair_number++;
            
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
// |      voi ch'entrate.     |
// |__________________________|
//

// This method iterates over all sprites known to the engine, and renders a
// frame with them.  
void Engine::render_frame(Frame* rendered_frame)
{
    // Create frame for window
    //int h, w;
    //getmaxyx(stdscr, h, w);
    
    //Frame f(h, w);

    // Loop over each 'pixel' in frame
    int h = rendered_frame->get_height();
    for (int y = (int)(-h/2); y < (int)(h/2); y++)
    {
        // Create row
        //vector<pixel> line;
        
        int w = rendered_frame->get_width();
        for (int x = (int)(-w/2); x < (int)(w/2); x++)
        {
            // Get current pixel of frame
            Pixel *rendered_pixel = rendered_frame->get_pixel(y + (int)(h/2), x + (int)(w/2));
            
            // Reset pixel
            rendered_pixel->clear();
            
            // Loop over each sprite, and write to current frame
            //vector<Sprite*>::iterator sprite;
            //for (sprite = sprites.begin(); sprite != sprites.end(); sprite++)
            for (int sprite_num = 0, size = sprites.size(); sprite_num < size; sprite_num++)
            {
                Sprite* current_sprite = sprites[sprite_num];
                
                Pixel new_pixel = Pixel(' ', Color(0, 0, 0, 0), Color(0, 0, 0, 0), false);
                
                // Make sure sprite is at least in front of the rendering plane
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (current_sprite->get_z_position() >= (z_camera_position /*- drawing_plane_distance*/))
                    continue;
                
                //                     ________
                //                    | Object |
                //     rendered       /¯¯¯¯¯¯¯¯
                //      pixel        /|
                //            \     / |
                //             \   /  |
                //              ┘ /   |
                //---------------X---------------------  <- drawing_plane
                //              /|    |
                //             / |    | <------- z_camera_position - current_sprite->get_z_position()
                //            /  | <------------ drawing_plane_distance
                //           /   |    |
                //         _/____|____|
                //         \_/ ^    ^-----(x/y) * z_diff_ratio
                //         | | └----------(x/y) 
                //          ¯
                //          ^- camera
                //
                
                float z_diff_ratio = (z_camera_position - current_sprite->get_z_position()) / (float)drawing_plane_distance;
                
                long int rel_x = (int)(x_camera_position + (x * z_diff_ratio) - current_sprite->get_x_position());
                long int rel_y = (int)(y_camera_position + (y * z_diff_ratio) - current_sprite->get_y_position());
                
                // If pixel overlaps with sprite
                if ( 0 <= rel_x && rel_x < current_sprite->get_width() &&
                     0 <= rel_y && rel_y < current_sprite->get_height())
                {
                    // Get pixel of interest
                    Pixel *current_pixel = current_sprite->get_pixel(rel_x, rel_y);
                        
                    // Determine if pixel should be drawn
                    // If the foreground alpha channel is anything but 0, it will be drawn
                    if (current_pixel->get_foreground_color()->get_alpha() != 0)
                    {
                        // Write character to pixel
                        new_pixel.set_char(current_pixel->get_char());

                        // TODO: THIS PROBABLY WON'T WORK FOR TRANSPARENT COLORS
                        // Write initial colors to pixel
                        new_pixel.set_foreground_color(*(current_pixel->get_foreground_color()));
                        new_pixel.set_background_color(*(current_pixel->get_background_color()));

                        // What color light is going to be applied to this pixel
                        static Color c = Color(0, 0, 0, 0);

                        // Handle dynamic lighting
                        if (current_sprite->respects_light_sources())
                        {
                            // Calculate new color based on nearby light sources
                            // Iterate over all light sources known to the engine
                            for (int light_num = 0, size = lights.size(); light_num < size; light_num++)
                            {
                                Light* current_light = lights[light_num];
                            
                                long int abs_x = current_sprite->get_x_position() + rel_x;
                                long int abs_y = current_sprite->get_y_position() + rel_y;
                                long int abs_z = current_sprite->get_z_position();
                                
                                // Light color at location
                                Color light_color = current_light->get_color(abs_x, abs_y, abs_z);
                                
                                // Compare normals to get light intensity
                                if (current_sprite->compare_normals())
                                {
                                    // Get vectors
                                    const Vector* pixel_normal = current_pixel->get_normal();
                                    const Vector light_vector = current_light->get_vector(current_sprite->get_x_position(), current_sprite->get_y_position(), abs_z);
                                
                                    // Get vector components
                                    char x1 = pixel_normal->get_x_component();
                                    char y1 = pixel_normal->get_y_component();
                                    char z1 = pixel_normal->get_z_component();
                                    char x2 = light_vector.get_x_component();
                                    char y2 = light_vector.get_y_component();
                                    char z2 = light_vector.get_z_component();
                                    
                                    // Calculate angle between the two
                                    float angle = acos((x1 * x2 + y1 * y2 + z1 * z2) / (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) * sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2))));
                                    
                                    // Scale from 0 to pi, to between 0 and 255
                                    unsigned char brightness = 255 - (unsigned char)(angle * 81.1690378636);
                                    
                                    // Adjust light brightness accordingly
                                    light_color.set_brightness(brightness);
                                }
                            
                                c += light_color;
                            }
                            
                            // Calculate reflected light based on available light
                            new_pixel.set_foreground_color(c * (*(new_pixel.get_foreground_color())));
                            new_pixel.set_background_color(c * (*(new_pixel.get_background_color())));
                            
                        }
                        else
                        {
                            // Write foreground color to pixel
                            new_pixel.set_foreground_color(*(current_pixel->get_foreground_color()));
                            new_pixel.set_background_color(*(current_pixel->get_background_color()));
                        }
                        
                        // Write bold to pixel
                        new_pixel.set_bold(current_pixel->get_bold());
                        
                        // Write underline to pixel
                        new_pixel.set_underline(current_pixel->get_underline());
                    }
                    
                }
                
                *rendered_pixel = new_pixel & *rendered_pixel;

            }
            
        }

    }

    static unsigned int frames;
    
    // Keep track of number of frames until second elapses
    long long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    
    if (now - last_count_time > 1000)
    {
        actual_frame_rate = frames;
        frames = 0;
    
        // Last run time
        last_count_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    }

    rendered_frame->add_string(1, 0, "FPS: " + std::to_string(actual_frame_rate));
    rendered_frame->add_string(2, 0, "CURRENT DIMENSIONS: " + std::to_string(rendered_frame->get_width())
                                     + "x" + std::to_string(rendered_frame->get_height()));
    rendered_frame->add_string(3, 0, "NUM SPRITES: " + std::to_string(sprites.size()));
    rendered_frame->add_string(4, 0, "NUM LIGHTS: " + std::to_string(lights.size()));
    rendered_frame->add_string(5, 0, "CAMERA LOCATION: (" + std::to_string(x_camera_position) + ", "
                                                          + std::to_string(y_camera_position) + ", "
                                                          + std::to_string(z_camera_position) + ")");
    rendered_frame->add_string(6, 0, "WILL TO LIVE: " + std::to_string(0));
    
    
    frames++;
    
    return;

}
