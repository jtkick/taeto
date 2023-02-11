// The Object class is designed to simply be a way to group sprites to mimic
// a 3D object. It is mainly a map where the 'key' is the z difference between
// the object and the camera. Each 'value' entry is the sprite which should
// be rendered when the object is 'key' lengths away from the camera.

#ifndef OBJECT_H
#define OBJECT_H

#include "components/object.h"
#include "components/sprite.h"

#include <map>

using namespace std;

class Object
{
    protected:

        // Sprites for draw distances
        // '-1' denotes the default, regardless of distance
        map<long int, Sprite*> sprites;

    public:

        Object();

};

#endif
