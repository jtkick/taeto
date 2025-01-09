// This file is a proof of concept for Taeto

using namespace std;

#include "engine.hpp"

// #include "assets/scenes/opening_island.h"
// #include "assets/scenes/collision_detection_test.hpp"
#include "assets/scenes/demo.hpp"
#include "assets/scenes/hdr_test.hpp"
// #include "assets/scenes/light_mixing_test.hpp"
// #include "assets/scenes/light_filter_test.h"
#include "assets/scenes/normal_mapping_test.hpp"
#include "assets/scenes/simple_test.hpp"
#include "assets/scenes/window_test.hpp"
// #include "assets/scenes/sprite_orientation_test.hpp"
// #include "assets/scenes/test_scene.h"

// #include "assets/objects/zero.h"

#include <tclap/CmdLine.h>
#include "spdlog/spdlog.h"


// Temp
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>




#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <string.h>

int main(int argc, char** argv)
{

    spdlog::set_level(spdlog::level::warn);

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

    taeto::set_debug_mode(true);
    if (test_scene == "demo")
        taeto::load_scene(std::make_shared<taeto::Demo>());
    else if (test_scene == "hdr_test")
        taeto::load_scene(std::make_shared<taeto::HDRTest>());
    else if (test_scene == "normal_mapping")
        taeto::load_scene(std::make_shared<taeto::NormalMappingTest>());
    else if (test_scene == "simple_test")
        taeto::load_scene(std::make_shared<taeto::SimpleTest>());
    else if (test_scene == "window_test")
        taeto::load_scene(std::make_shared<taeto::WindowTest>());
    else
        taeto::set_debug_mode(false);

    taeto::run();
}
