#ifndef FRAME_H
#define FRAME_H

#include "Pixel.h"

#include <array>
#include <string>

using namespace std;

class Frame
{
    private:
    
        // Frame dimensions
        unsigned long int width;
        unsigned long int height;
        
        // Pixels that frame is made up of
        vector<vector<Pixel>> pixels;
        
    public:

        //Frame();
        
        Frame(unsigned long int, unsigned long int);
        
        // Destructor
        ~Frame();
        
        // Getters and setters
        Pixel get_pixel(long int, long int);
        
        unsigned long int get_width();
        
        unsigned long int get_height();
        
        void set_pixel(long int, long int, Pixel);
        
        void set_width(unsigned long int);
        
        void set_height(unsigned long int);
 
        // Set just the characters of single pixel in frame
        void set_char(unsigned long int, unsigned long int, char);
        
        // Set just the characters of all pixels in frame
        void set_chars(vector<string>);
        
        // Set just the foreground colors of all pixels in frame
        void set_foreground_colors(vector<vector<Color>>);
        
        // Set just the foreground color of single pixel in frame
        void set_foreground_color(unsigned long int, unsigned long int, Color);
        
        // Set just the background colors of all pixels in frame
        void set_background_colors(vector<vector<Color>>);
        
        // Set just the background color of single pixel in frame
        void set_background_color(unsigned long int, unsigned long int, Color);
        
        // Set just the bold parameter of all pixels in frame
        void set_bolds(vector<vector<bool>>);
        
        // Set just the bold parameter of single pixel in frame
        void set_bold(unsigned long int, unsigned long int, bool);
        
        // Helper methods
        
        // Write string to given location in frame
        void add_string(long int, long int, string);
        
        // Maps frame onto this frame wherever current frame has the given character
        void map(Frame f, char c); 
};

#endif