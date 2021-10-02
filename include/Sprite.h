#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Frame.h"
#include "Pixel.h"

#include <chrono>
#include <map>
#include <memory>
#include <string>
#include <vector>

// for debugging
#include <iostream>

using namespace std;

class Sprite
{
    protected:

    // Position on screen relative to origin
    // Top 32 bits are pixel position, bottom 32 bits are sub-pixel position
    // This allows for positions and speeds that aren't tied to frame rate
    int64_t x_position;
    int64_t y_position;
    int64_t z_position;

    // Size of sprite
    uint32_t width;
    uint32_t height;
    uint32_t depth;

    // Current forces on object
    double x_force;
    double y_force;
    double z_force;

    // Current speed in pixels per second per second
    // To be updated by the physics system
    double x_speed;
    double y_speed;
    double z_speed;

    // Objects mass
    // Idk what the unit is, it doesn't matter, it's just a ratio with the forces
    double mass;

    // Time at which forces were last applied to sprite by physics system
    long long time_physics_last_applied;

    // Each element of the dict is 3D model of what this particular sprite
    // should look like at this distance from the camera, taking zoom into
    // account. The engine will determine based on the camera's relative
    // z position and zoom level, how big the sprite should appear on screen,
    // and look for the appropriate model in the following dict.
    //map<long int, Model> models;

    // Time at which the last frame was animated in milliseconds since UNIX epoch
    long long last_run_time;

    // Character that denotes that the given 'pixel' should not be drawn
    char alpha_char = ' ';

    // Current frame as it should be displayed
    // Must be defined everytime animate() is called
    Frame current_frame = Frame(0, 0);

    unsigned int current_frame_index = 0;

    // Place to store useful frames
    vector<Frame> frames;

    // True if this sprite should collide with any other sprite that also
    // has this member set to true
    bool collide;

    // True if physics_system should check for collisions with this sprite
    // If this is false and 'collide' is true, this sprite will collide with
    // other sprites, but the physics system won't check with this sprite
    bool detect_collisions;

    // Let the engine decide the color of this sprite based on light sources
    bool respect_light_sources = false;

    // Whether or not engine looks at normal to determine light brightness
    // Only applies if respect_light_sources is true
    bool use_normal_mapping = false;

    // If this sprite is entirely off screen, this determines if the animate() function is called
    bool animate_off_screen = false;

    // True if this sprite was rendered on the last call to render_frame in the Render_System
    bool visible;


    public:

        // Sprites that this sprite is made out of
        // Any transformation/translation of this sprite will be done to sub_sprites
        vector<Sprite*> sub_sprites;

        Sprite();

        Sprite(long int, long int, long int);

        ~Sprite();

        shared_ptr<Pixel> get_pixel(long int, long int);

        int64_t get_height();

        int64_t get_width();

        int32_t get_x_pixel_position();

        int32_t get_y_pixel_position();

        int32_t get_z_pixel_position();

        int64_t get_x_exact_position();

        int64_t get_y_exact_position();

        int64_t get_z_exact_position();

        double get_x_force();

        double get_y_force();

        double get_z_force();

        double get_x_speed();

        double get_y_speed();

        double get_z_speed();

        double get_mass();

        long long get_time_physics_last_applied();

        bool is_visible();

        bool get_collide();

        bool get_detect_collisions();

        bool respects_light_sources();

        bool compare_normals();

        void set_x_pixel_position(int32_t);

        void set_y_pixel_position(int32_t);

        void set_z_pixel_position(int32_t);

        void set_x_exact_position(int64_t);

        void set_y_exact_position(int64_t);

        void set_z_exact_position(int64_t);

        void set_x_speed(double);

        void set_y_speed(double);

        void set_z_speed(double);

        void set_mass(double);

        void set_time_physics_last_applied(long long);

        void set_frame_chars(vector<string>);

        void set_visible(bool);

        // Moving to Frame
        //void map_sprite(char, Sprite*, long int, long int);

        // Returns true if sprite collides with given sprite
        bool collides_with(shared_ptr<Sprite>);

        // Method define by child sprite
        // Defines what to do when this sprite collides with another
        virtual void handle_collision(shared_ptr<Sprite>);

        void move(long int, long int, long int);

        virtual void animate();

};

#endif
