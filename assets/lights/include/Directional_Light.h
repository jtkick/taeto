#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"
#include "Color.h"
#include "Vector.h"

using namespace std;

class Directional_Light: public Light
{
    public:
    
        Color color;
    
        Vector vector;
    
        Directional_Light();
        
        Directional_Light(Color, Vector);
        
        Color get_color(long int, long int, long int);
        
        Vector get_vector(long int, long int, long int);

};

#endif
