#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"
#include "Color.h"
#include "Vector.h"

using namespace std;

class Spotlight: public Light
{
    public:
    
        Color color;
    
        float fade;
        
        unsigned int radius;
    
        Spotlight();
        
        Spotlight(Color, float, int);
        
        Color get_color(long int, long int, long int);
        
        Vector get_vector(long int, long int, long int);
        
};

#endif
