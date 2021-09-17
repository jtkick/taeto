#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Frame.h"
#include "Pixel.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <chrono>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Sprite
{
    protected:

    // Position on screen relative to origin
    // TODO: Top 32 bits are pixel position, bottom 32 bits are sub-pixel position
    // This allows for positions and speeds that aren't tied to frame rate
    long int x_position;
    long int y_position;
    long int z_position;

    // Size of sprite
    unsigned long int width;
    unsigned long int height;
    //unsigned long int depth;

    // Each element of the dict is 3D model of what this particular sprite
    // should look like at this distance from the camera, taking zoom into
    // account. The engine will determine based on the camera's relative
    // z position and zoom level, how big the sprite should appear on screen,
    // and look for the appropriate model in the following dict.
    //map<long int, Model> models;

    // Time at which the last frame was animated in milliseconds since UNIX epoch
    long long last_run_time;

    // Current frame as it should be displayed
    // Must be defined everytime animate() is called
    Frame current_frame = Frame(0, 0);

    // Denotes whether or not the current sprite should collide with other sprites
    bool collides = false;

    // Whether or not the engine checks for collision on this object
    bool detect_collisions = false;

    // Denotes which frame in the list should be used for the current game frame
    unsigned int current_frame_index = 0;

    // Place to store useful frames
    std::map<string, Frame> frames;

    // Let the engine decide the color of this sprite based on light sources
    bool respect_light_sources = false;

    // Whether or not engine looks at normal to determine light brightness
    // Only applies if respect_light_sources is true
    bool use_normal_mapping = false;

    // If this sprite is entirely off screen, this determines if the animate() function is called
    bool animate_off_screen = false;

    // Remove this at some point
    char alpha_char = 'R';

    private:

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & x_position;
            ar & y_position;
            ar & z_position;
            ar & width;
            ar & height;
            ar & collides;
            ar & detect_collisions;
            ar & frames;
            ar & respect_light_sources;
            ar & use_normal_mapping;
            ar & animate_off_screen;
        }

    public:

        // Sprites that this sprite is made out of
        // Any transformation/translation of this sprite will be done to sub_sprites
        vector<Sprite*> sub_sprites;

        Sprite();

        Sprite(unsigned long int, unsigned long int);

        Sprite(long int, long int, long int);

        ~Sprite();

        Pixel* get_pixel(long int, long int);

        // Returns pointer to frame with given name
        // Should only be used by the sprite designer
        Frame* get_frame(string);

        long int get_height();

        long int get_width();

        long int get_x_position();

        long int get_y_position();

        long int get_z_position();

        bool respects_light_sources();

        bool compare_normals();

        void set_frame_chars(vector<string>);

        // Moving to Frame
        //void map_sprite(char, Sprite*, long int, long int);

        void move(long int, long int, long int);

        virtual void animate();

        ///////////////////////////////////////////////////////////////////////
        ///                        DESIGN METHODS                           ///
        ///////////////////////////////////////////////////////////////////////
        /// The following methods are used to design the sprite. They ought
        /// to only be called by PTSD and not after the program begins.

        // Adds frame to sprite, using the given string as the key
        void add_frame(string);

        // Just prints the names of all frames for debugging purposes
        void print_frames();

        // Deletes frame with the given name
        void remove_frame(string);

        // Changes name of a frame in the map
        void rename_frame(string, string);

        // Destructive method that changes sprites dimensions including sub-frames
        void resize(unsigned long int, unsigned long int);
};

#endif
