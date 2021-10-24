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
#include "Collision_Detection_Test.h"
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


int main(int argc, char** argv)
{
    Engine engine;

    try
    {
        // Set description
        TCLAP::CmdLine cmd("Taeto is a program designed to create ASCII animations in the terminal.", ' ', "0.9");

        // Option to load test scenes
        TCLAP::ValueArg<std::string> test_scene_arg("t", "test", "Test scene to load.", false, "", "string");
        cmd.add(test_scene_arg);

        // Parse arguments
        cmd.parse(argc, argv);

        // Load test scene
        std::string test_scene_name = test_scene_arg.getValue();
        if (test_scene_name == "collision_detection")
        {
            shared_ptr<Collision_Detection_Test> cdt = make_shared<Collision_Detection_Test>();
            engine.load_scene(cdt);
        }
        else if (test_scene_name == "normal_mapping")
        {
            shared_ptr<Normal_Mapping_Test> nmt = make_shared<Normal_Mapping_Test>();
            engine.load_scene(nmt);
        }
        else if (test_scene_name == "light_mixing")
        {
            shared_ptr<Light_Mixing_Test> lmt = make_shared<Light_Mixing_Test>();
            engine.load_scene(lmt);
        }
    }
    catch (TCLAP::ArgException &e)
    {
        std::cerr << "Error: " << e.error() << " for arg " << e.argId() << std::endl;
        throw "e";
    }

    main_character person;
    person.move(0, 0, -10);

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


    engine.run();

}
