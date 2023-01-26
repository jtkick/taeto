// This file is a proof of concept for Taeto

using namespace std;

#include "Engine.h"

#include "Opening_Island.h"
#include "Collision_Detection_Test.h"
#include "Light_Mixing_Test.h"
#include "Normal_Mapping_Test.h"
#include "Test_Scene.h"


#include "char_frame.h"


#include "Zero.h"

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


    Engine engine;


    if (test_scene == "collision_detection")
    {
        shared_ptr<Collision_Detection_Test> cdt = make_shared<Collision_Detection_Test>();
        engine.load_scene(cdt);
    }
    else if (test_scene == "normal_mapping")
    {
        shared_ptr<Normal_Mapping_Test> nmt = make_shared<Normal_Mapping_Test>();
        engine.load_scene(nmt);
    }
    else if (test_scene == "light_mixing")
    {
        shared_ptr<Light_Mixing_Test> lmt = make_shared<Light_Mixing_Test>();
        engine.load_scene(lmt);
    }
    else
    {
        // Load opening island
        //shared_ptr<Opening_Island> oi = make_shared<Opening_Island>();
        //engine.load_scene(oi);

        shared_ptr<Test_Scene> ts = make_shared<Test_Scene>();
        engine.load_scene(ts);
    }

    engine.run();

    // CharFrame f = CharFrame("/home/jared/load_png_test.png");
    //
    // f.print();

}
