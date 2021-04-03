#ifndef ENGINE_H
#define ENGINE_H

#include "Sprite.h"
#include "Light.h"

#include <curses.h>
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include <unistd.h>

class Engine
{
public:
    // Sprites to render
    vector<Sprite*> sprites;

    // Light sources
    vector<Light*> lights;

    // Frame rate to aim for
    unsigned int target_frame_rate = 0;

    // Actual rate engine is running at
    unsigned int actual_frame_rate = 0;

    // Possibly temporary
    long long last_count_time = 0;

    // Camera position
    long int x_camera_position;
    long int y_camera_position;
    long int z_camera_position;

    // If set to true, engine will display FPS in top left corner
    bool display_frame_rate;

    public:

        Engine(void);

        ~Engine(void);

        void add_light(Light*);

        void add_sprite(Sprite*);

        void animate();

        void display_frame(Frame*);

        void display_frame_ncurses(Frame*);

        void move_camera(long int, long int, long int);

        void render_frame(Frame*);

};

#endif
