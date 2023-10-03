// This file is a proof of concept for Taeto

using namespace std;

#include "engine.hpp"

// #include "assets/scenes/opening_island.h"
// #include "assets/scenes/collision_detection_test.hpp"
// #include "assets/scenes/light_mixing_test.hpp"
// #include "assets/scenes/light_filter_test.h"
#include "assets/scenes/normal_mapping_test.hpp"
#include "assets/scenes/simple_test.hpp"
// #include "assets/scenes/sprite_orientation_test.hpp"
// #include "assets/scenes/test_scene.h"

// #include "assets/objects/zero.h"

#include <tclap/CmdLine.h>

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <string.h>

int main(int argc, char** argv)
{

    // shared_ptr<sf::Music> music = make_shared<sf::Music>();
    // if (!music->openFromFile("/home/jared/Desktop/Dream Sweet in Sea Major - truncated.wav"))
    //    exit(-1);
    // music->setVolume(50);
    // music->play();

    // Test scene to load if any
    std::string test_scene;

    try
    {
        // Set description
        TCLAP::CmdLine cmd("Taeto is a program designed to create ASCII animations in the terminal.", ' ', "0.9");

        // Option to load test scenes
        TCLAP::ValueArg<std::string> test_scene_arg("t", "test", "Test scene to load.", false, "", "string");
        cmd.add(test_scene_arg);

        // Parse arguments
        cmd.parse(argc, argv);

        // Get test scene to load
        test_scene = test_scene_arg.getValue();
    }
    catch (TCLAP::ArgException &e)
    {
        std::cerr << "Error: " << e.error() << " for arg " << e.argId() << std::endl;
        throw "e";
    }


    // Test export
    //Zero z;
    //z.serialize("/home/jared/zero.csv", true);
    //return 0;


    // taeto::Engine engine;


    // if (test_scene == "collision_detection")
    //     taeto::load_scene(std::make_shared<taeto::CollisionDetectionTest>());
    if (test_scene == "normal_mapping")
        taeto::load_scene(std::make_shared<taeto::NormalMappingTest>());
    else if (test_scene == "simple_test")
        taeto::load_scene(std::make_shared<taeto::SimpleTest>());
    // else if (test_scene == "light_mixing")
    //     taeto::load_scene(std::make_shared<taeto::LightMixingTest>());
    // else if (test_scene == "sprite_orientation")
    //     taeto::load_scene(std::make_shared<taeto::SpriteOrientationTest>());

    // else if (test_scene == "light_filter")
    // {
    //     shared_ptr<LightFilterTest> lft = make_shared<LightFilterTest>();
    //     engine.load_scene(lft);
    // }
    // else
    // {
    //     // Load opening island
    //     //shared_ptr<Opening_Island> oi = make_shared<Opening_Island>();
    //     //engine.load_scene(oi);
    //
    //     shared_ptr<Test_Scene> ts = make_shared<Test_Scene>();
    //     engine.load_scene(ts);
    // }

    taeto::run();

    // CharFrame f = CharFrame("/home/jared/load_png_test.png");
    //
    // f.print();

}
