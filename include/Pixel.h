#ifndef STRUCTS
#define STRUCTS

#include <Color.h>

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
        Color foreground_color;
        
        // Color of background of 'pixel'
        Color background_color;
 
        // Whether or not this 'pixel' should be printed in bold
        bool bold = false;
        
        // Whether or not the 'pixel' is underlined
        bool underline = false;
        
    public:
    
        // Constructors
        Pixel();
        
        Pixel(char);
        
        Pixel(char, Color, Color, bool);
        
        // Getters and setters
        char get_char() const;
        
        Color get_foreground_color() const;
        
        Color get_background_color() const;
        
        bool get_bold() const;
        
        bool get_underline() const;
        
        void set_char(char);
        
        void set_foreground_color(Color);
        
        void set_background_color(Color);
        
        void set_bold(bool);
        
        void set_underline(bool);
        
        void operator = (const Pixel &p);
        
        // Reset to default values
        void clear();
        
        //void operator + (const Pixel &p);
};

#endif
