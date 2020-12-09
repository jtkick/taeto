#ifndef STRUCTS
#define STRUCTS

#include <vector>
#include <stdint.h>

using namespace std;

class Pixel
{
    private:
    
        // Actual character to print
        char c = '\0';
    
        // Color of this 'pixel'
        // Based on whatever color palette is set in the engine
        uint8_t foreground_color = 0;
        
        // Color of background of 'pixel'
        uint8_t background_color = 0;
 
        // Whether or not this 'pixel' should be printed in bold
        bool bold = false;
        
    public:
    
        // Constructors
        Pixel();
        
        Pixel(char, int16_t, int16_t, int8_t);
        
        // Getters and setters
        char get_char() const;
        
        uint8_t get_foreground_color() const;
        
        uint8_t get_background_color() const;
        
        bool get_bold() const;
        
        void set_char(char);
        
        void set_foreground_color(uint8_t);
        
        void set_background_color(uint8_t);
        
        void set_bold(bool);
        
        void operator = (const Pixel &p);
        
        void operator + (const Pixel &p);
};

#endif
