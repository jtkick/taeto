#ifndef FRAME_H
#define FRAME_H

#include "structs.h"

#include <string>
#include <vector>

using namespace std;

class Frame
{
    public:

        Frame();
        
        Frame(unsigned long int, unsigned long int);
        
        // Getters and setters
        pixel get_pixel(long int, long int);
        
        unsigned long int get_width();
        
        unsigned long int get_height();
        
        void set_pixel(long int, long int, pixel);
        
        void set_width(unsigned long int);
        
        void set_height(unsigned long int);
        
        // Set just the characters of all pixels in frame
        void set_chars(vector<string>);
        
        // Set just the colors of all pixels in frame
        void set_colors(vector<vector<unsigned char>>);
        
        // Set just the bold parameter of all pixels in frame
        void set_bolds(vector<vector<bool>>);
        
        
    private:
    
        // Frame dimensions
        unsigned long int width;
        unsigned long int height;
        
        // Pixels that frame is made up of
        pixel** pixels;
        
};

#endif
