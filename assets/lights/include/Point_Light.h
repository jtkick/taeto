#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"
#include "Color.h"

using namespace std;

class Point_Light: public Light
{
    public:
    
        float fade;
    
        Point_Light();
        
        Point_Light(Color, float);
        
        Color get_color(long int, long int, long int);
        
        Vector get_vector(long int, long int, long int);
        
};

#endif
