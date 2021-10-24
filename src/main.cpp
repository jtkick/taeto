// This file is a proof of concept for Taeto

using namespace std;

#include "Engine.h"
#include "Sprite.h"
#include "Frame.h"
#include "Light.h"

#include "Point_Light.h"
#include "Spotlight.h"
#include "Directional_Light.h"

#include "Opening_Island.h"
#include "Light_Mixing_Test.h"
#include "Normal_Mapping_Test.h"

#include <tclap/CmdLine.h>

#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>


class main_character: public Sprite
{

    public:

        void handle_collision(shared_ptr<Sprite>);

        unsigned long long last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

        main_character() {

            // Default position to the origin
            x_position = 0;
            y_position = 0;
            z_position = 0;

            // Set frame details
            height = 2;
            width = 6;

            mass = 1;
            y_force = 200000000000;

            collide = true;
            detect_collisions = true;

            //current_frame = new Frame(7, 7);
            Frame f = Frame(height, width);

            Color w = Color(255, 255, 255);
            Color g = Color(43, 43, 43);
            Color a = Color(255, 255, 255, 0);

            f.set_chars({ R"(@@__@@)",
                          R"(@( ')')"});
            f.set_foreground_colors( { { a, a, g, g, a, a },
                                       { a, g, g, g, g, g } } );
            f.set_background_colors( { { w, w, a, a, w, w },
                                       { w, w, w, w, w, w } } );

            current_frame = f;

            respect_light_sources = false;

        }

        shared_ptr<Frame> get_current_frame()
        {
            return make_shared<Frame>(current_frame);
        }
};

void main_character::handle_collision(shared_ptr<Sprite> sprite_ptr)
{
    // Null y speed
    this->set_y_speed(0.0);

    // Move up
    while (this->collides_with(sprite_ptr))
        this->set_y_pixel_position(this->get_y_pixel_position() - 1);
}


class Color_Test: public Sprite
{
    public:

    Color_Test() {
        x_position = 0;
        y_position = 0;
        z_position = 0;

        height = 1;
        width = 8;
        Frame f = Frame(height, width);
        f.set_chars({ R"(XXXXXXXXX)" });

        Color r = Color(255, 0, 0);
        Color o = Color(255, 127, 0);
        Color y = Color(255, 255, 0);
        Color g = Color(0, 255, 0);
        Color b = Color(0, 255, 255);
        Color i = Color(0, 127, 255);
        Color v = Color(0, 0, 255);
        Color w = Color(255, 255, 255);

        f.set_foreground_colors({{ r, o, y, g, b, i, v, w }});

        current_frame = f;
    }

    shared_ptr<Frame> get_current_frame()
    {
        return make_shared<Frame>(current_frame);
    }
};

class Floor_Test: public Sprite
{
    public:
        Floor_Test() {
            x_position = -10;
            y_position = 0;
            z_position = 0;

            height = 5;
            width = 20;

            respect_light_sources = false;
            use_normal_mapping = false;

            collide = true;

            Frame f = Frame(height, width);
            f.set_chars({ R"(XXXXXXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXXXXXX)" });

            Color r = Color(255, 0, 0);

            f.set_foreground_colors({{ r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r },
                                     { r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r },
                                     { r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r },
                                     { r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r },
                                     { r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r }});
            current_frame = f;
        }

        shared_ptr<Frame> get_current_frame() {
            return make_shared<Frame>(current_frame);
        }
};


int main()
{
    TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

    Engine engine;

    //Palm_tree tree;
    //tree.move(0, 0, -10);

    main_character person;
    person.move(0, 0, -10);

    //Palm_tree more_trees[100];
    //for (int i = 0; i < 100; i++)
    //    engine.add_sprite(&more_trees[i]);

    //ground1 g;
    //g.move(0, 22, -1);

    //engine.add_sprite(&g);

    //engine.add_sprite(make_shared<Sprite>(tree));

    Floor_Test ft;
    ft.move(-5, 20, -10);
    engine.add_sprite(make_shared<Floor_Test>(ft));

    engine.add_sprite(make_shared<main_character>(person));

    shared_ptr<Point_Light> p = make_shared<Point_Light>(Color(255, 255, 255), 0.9999);
    //engine.add_light(p);

    //std::cout << "Creating opening island scene." << std::endl;
    //shared_ptr<Opening_Island> o = make_shared<Opening_Island>();
    //std::cout << "Loading island scene." << std::endl;
    //engine.load_scene(o);

    //shared_ptr<Light_Mixing_Test> lmt = make_shared<Light_Mixing_Test>();
    //engine.load_scene(lmt);

    shared_ptr<Normal_Mapping_Test> nmt = make_shared<Normal_Mapping_Test>();
    engine.load_scene(nmt);


    engine.run();

}
