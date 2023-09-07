#ifndef COMPONENTS_SPRITE_H_
#define COMPONENTS_SPRITE_H_

#include <chrono>
#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include <iostream>

namespace taeto
{

class Sprite
{
    public:

        // Define which plane the object will be drawn on
        // Object will almost always be on plane Z, walls on plane Y, and
        // floors and ceilings on plane X
        char plane_orientation_;

        // Position on screen relative to origin
        // Top 32 bits are pixel position, bottom 32 bits are sub-pixel position
        // This allows for positions and speeds that aren't tied to frame rate
        int64_t x_position;
        int64_t y_position;
        int64_t z_position;

        // Size of sprite
        uint32_t width;
        uint32_t height;

        // Scaling factor to fudge the size of a sprite
        double scaling_factor;

        // Current speed in pixels per second per second
        // To be updated by the physics system
        double x_speed;
        double y_speed;
        double z_speed;

        // Current forces on object
        double x_force;
        double y_force;
        double z_force;

        // Object's mass
        // Idk what the unit is, it doesn't matter, it's just a ratio with the forces
        double mass;

        // Tags used by scenes to keep track of what an object is, like walls and floors
        uint64_t tags;

        // True if this sprite should collide with any other sprite that also
        // has this member set to true
        bool collide;

        // True if physics_system should check for collisions with this sprite
        // If this is false and 'collide' is true, this sprite will collide with
        // other sprites, but the physics system won't check with this sprite
        bool detect_collisions;

        // Let the engine decide the color of this sprite based on light sources
        bool respect_light_sources;

        // Whether or not engine looks at normal to determine light brightness
        // Only applies if respect_light_sources is true
        bool use_normal_mapping;

        // If this sprite is entirely off screen, this determines if the animate() function is called
        bool animate_off_screen;

    // Members used by the engine, should not be changed manually
    private:

        // Time at which forces were last applied to sprite by physics system
        long long time_physics_last_applied;

        // True if this sprite was rendered on the last call to render_frame in the Render_System
        bool visible;

    public:

        ////////////////////////////////////////////////////////////////////////
        ///                           CONSTRUCTORS                           ///
        ////////////////////////////////////////////////////////////////////////
        Sprite();

        Sprite(long int, long int, long int);

        ////////////////////////////////////////////////////////////////////////
        ///                            DESTRUCTOR                            ///
        ////////////////////////////////////////////////////////////////////////
        ~Sprite();

        ////////////////////////////////////////////////////////////////////////
        ///                             GETTERS                              ///
        ////////////////////////////////////////////////////////////////////////
        char get_plane_orientation();

        int32_t get_x_pixel_position();

        int32_t get_y_pixel_position();

        int32_t get_z_pixel_position();

        int64_t get_x_exact_position();

        int64_t get_y_exact_position();

        int64_t get_z_exact_position();

        int64_t get_height();

        int64_t get_width();

        double get_scaling_factor();

        double get_x_speed();

        double get_y_speed();

        double get_z_speed();

        double get_x_force();

        double get_y_force();

        double get_z_force();

        double get_mass();

        uint64_t get_tags();

        bool get_collide();

        bool get_detect_collisions();

        bool get_respect_light_sources();

        bool get_use_normal_mapping();

        bool get_animate_off_screen();

        long long get_time_physics_last_applied();

        bool get_visible();

        ////////////////////////////////////////////////////////////////////////
        ///                             SETTERS                              ///
        ////////////////////////////////////////////////////////////////////////
        void set_plane_orientation(char);

        void set_x_pixel_position(int32_t);

        void set_y_pixel_position(int32_t);

        void set_z_pixel_position(int32_t);

        void set_x_exact_position(int64_t);

        void set_y_exact_position(int64_t);

        void set_z_exact_position(int64_t);

        void set_scaling_factor(double);

        void set_x_speed(double);

        void set_y_speed(double);

        void set_z_speed(double);

        void set_x_force(double);

        void set_y_force(double);

        void set_z_force(double);

        void set_mass(double);

        void set_tags(uint64_t);

        void set_collide(bool);

        void set_detect_collisions(bool);

        void set_respect_light_sources(bool);

        void set_use_normal_mapping(bool);

        void set_animate_off_screen(bool);

        void set_current_frame(std::string);

        void set_time_physics_last_applied(long long);

        void set_visible(bool);

        ////////////////////////////////////////////////////////////////////////
        ///                           OPERATORS                              ///
        ////////////////////////////////////////////////////////////////////////

        bool operator < (const Sprite& other);

        ////////////////////////////////////////////////////////////////////////
        ///                         HELPER METHODS                           ///
        ////////////////////////////////////////////////////////////////////////

        // Returns true if sprite collides with given sprite
        bool collides_with(std::shared_ptr<Sprite>);

        // Export Sprite to CSV file for importing in Taeto
        void serialize(std::filesystem::path, bool);

        // Since the sprite allows fake scaling, we need a 'get_pixel()' method
        // instead of using the Frame directly, to handle the scaling
        const Pixel& get_pixel(long int, long int);

        // Move sprite and sub-sprite given distance in pixels
        void move(long int, long int, long int);

        // Saves sprite to given directory, for saving with PTSD
        void save(std::filesystem::path);

        ////////////////////////////////////////////////////////////////////////
        ///                       CHILD SPRITE METHODS                       ///
        ////////////////////////////////////////////////////////////////////////
        // The following methods are to be defined by any sprite which inherits
        // from this class. Not all necessarily need to be defined.

        // Defines what to do with the sprite each frame
        // Before rendering each frame, the engine will call 'animate()' on all
        // sprites known to the engine
        virtual void animate();

        // Defines what the sprite should look like currently, this should
        // include the current collision mesh
        virtual std::shared_ptr<Frame> get_current_frame();

        // Defines what the sprite should look like currently
        // This method instead returns a mipmap of sorts for any draw distance
        //virtual shared_ptr<Mipmap> get_current_frame();

        // Defines what to do when this sprite collides with another
        virtual void handle_collision(std::shared_ptr<Sprite>);
};

}   // namespace taeto

#endif  // COMPONENTS_SPRITE_H_
