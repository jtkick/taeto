#ifndef STRUCTS
#define STRUCTS

#include <vector>

struct pixel
{
    // Actual character to print
    char c = " ";
    
    // Color of this 'pixel'
    // Based on whatever color palette is set in the engine
    uint8_t color = 0;
 
    // Whether this 'pixel' should be printed in bold   
    bool bold = false;
};
    

#define frame vector<vector<pixel>>

#endif
