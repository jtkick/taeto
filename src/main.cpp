// This file is a proof of concept for Taeto

using namespace std;

#include "Engine.h"
#include "Sprite.h"
#include "Frame.h"
#include "Light.h"

#include "Point_Light.h"

#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>

// For getting window size info in UNIX
#include <sys/ioctl.h>
#include <unistd.h>

int w_char = 119;
int a_char = 97;
int s_char = 115;
int d_char = 100;
int space_char = 32;



class Bars: public Sprite
{
    public:

        Bars() {

            x_position = 0;
            y_position = 0;
            z_position = 0;

            respect_light_sources = true;

            height = 20;
            width = 84;


                Frame default_frame(20, 84);


                Color w = Color(255, 255, 255);  // White
                Color y = Color(255, 255, 0);    // Yellow
                Color c = Color(0, 255, 255);    // Cyan
                Color g = Color(0, 255, 0);      // Green
                Color p = Color(255, 0, 255);    // Pink
                Color r = Color(255, 0, 0);      // Red
                Color b = Color(0, 0, 255);      // Blue
                Color k = Color(0, 0, 0);        // Black
                Color a = Color(0, 26, 66);      // Navy
                Color u = Color(43, 0, 89);      // Purple

                default_frame.set_background_colors({
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b },
                    { w, w, w, w, w, w, w, w, w, w, w, w, y, y, y, y, y, y, y, y, y, y, y, y, c, c, c, c, c, c, c, c, c, c, c, c, g, g, g, g, g, g, g, g, g, g, g, g, p, p, p, p, p, p, p, p, p, p, p, p, r, r, r, r, r, r, r, r, r, r, r, r, b, b, b, b, b, b, b, b, b, b, b, b }
                });

                current_frame = default_frame;
                }
                };




class Palm_tree: public Sprite
{
    public:

        // I am going to kill myself
        Palm_tree() {

            // Default position to the origin
            x_position = 0;
            y_position = 0;
            z_position = 0;

            // Set frame details
            height = 22;
            width = 45;
            alpha_char = '@';
            vector<string> default_chars = {
                R"(@@@@@@@@@@@@@@_____@@@@@@@@@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@__/ / / \_@@@@@@@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@/ / / / / /\@@@@@@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@\/\/\/ / / /\@@@@@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@\/\/_/ /\@@@@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@________@@\/ /|@@@@@________@@@@@@@)",
                R"(@@@@@____/ / / / /\__\/ |@___/_ \ \ \ \__@@@@)",
                R"(@@__/ / / / / / / / /\|/|/ \ \ \_\ \ \ \ \@@@)",
                R"(@/ / / / / / / / / / / \/ \ \ \ \ \_\_\ \ \@@)",
                R"(/ / / / /\/\/\/\/\/\/\|XX|/\ \ \ \ \@@@\_\ \@)",
                R"(|/\/\/\/@@@@@@@@@@@@@@|XX|@@\/\ \ \ \@@@@@\ |)",
                R"(@@@@@@@@@@@@@@@@@@@@@@|XX|@@@@@\/\ \|@@@@@@\|)",
                R"(@@@@@@@@@@@@@@@@@@@@@@\XX\@@@@@@@@\ |@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@|XX|@@@@@@@@\|@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@|XX|@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@\XX\@@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@@|XX|@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@@|XX|@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@@\XX\@@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@@@|XX\@@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@@/XXXX\@@@@@@@@@@@@@@@)",
                R"(@@@@@@@@@@@@@@@@@@@@@@@/XXXXXX\@@@@@@@@@@@@@@)" };

            Frame default_frame(22, 45);
            default_frame.set_chars(default_chars);

            // Trunk color
            Color t = Color(170, 166, 161);
            // Leaf color
            Color l = Color(105, 181, 130);
            // Fully alpha
            Color a = Color(0, 0, 0, 0);

            default_frame.set_foreground_colors({{ l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, t, t, t, t, l, l, l, l, l, l, l, l, l, l, a, a, a, l, l, l, l, l, a},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, t, t, t, t, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, t, t, t, t, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, t, t, t, t, t, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a},
            { a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, t, t, t, t, t, t, t, t, a, a, a, a, a, a, a, a, a, a, a, a, a, a}

            });

            current_frame = default_frame;

    }

};


class Person: public Sprite
{
    public:

        void animate();

        unsigned long long last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

        Person() {

            // Default position to the origin
            x_position = 0;
            y_position = 0;
            z_position = 0;

            // Set frame details
            height = 7;
            width = 7;
            alpha_char = '@';
            //current_frame = new Frame(7, 7);
            Frame f = Frame(7, 7);

            Color r = Color(255, 0, 0);
            Color b = Color(0, 0, 255);
            Color t = Color(255, 255, 255, 0);

            f.set_chars({ R"(@@___@@)",
                          R"(@/ ..\@)",
                          R"(@\_U_/@)",
                          R"((__|__@)",
                          R"(@@@|@@))",
                          R"(@@_|_@@)",
                          R"(@@|@|@@)" });
            f.set_foreground_colors( { { t, t, r, r, r, t, t },
                                       { t, r, r, r, r, r, t },
                                       { t, r, r, r, r, r, t },
                                       { r, r, r, r, r, r, t },
                                       { t, t, t, r, t, t, r },
                                       { t, t, r, r, r, t, t },
                                       { t, t, r, t, r, t, t } } );
            frames.push_back(f);

            f.set_chars({ R"(@@___@@)",
                          R"(@/.. \@)",
                          R"(@\_U_/@)",
                          R"(@__|__))",
                          R"((@@|@@@)",
                          R"(@@_|_@@)",
                          R"(@@|@|@@)" });
            f.set_foreground_colors( { { t, t, b, b, b, t, t },
                                       { t, b, b, b, b, b, t },
                                       { t, b, b, b, b, b, t },
                                       { t, b, b, b, b, b, b },
                                       { b, t, t, b, t, t, t },
                                       { t, t, b, b, b, t, t },
                                       { t, t, b, t, b, t, t } } );
            frames.push_back(f);




            //current_frame.set_chars(data[0]);

        }

};

class main_character: public Sprite
{
    public:

        unsigned long long last_run_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

        main_character() {

            // Default position to the origin
            x_position = 0;
            y_position = 0;
            z_position = 0;

            // Set frame details
            height = 3;
            width = 6;
            //current_frame = new Frame(7, 7);
            Frame f = Frame(height, width);

            Color w = Color(255, 255, 255);
            Color g = Color(43, 43, 43);
            Color a = Color(255, 255, 255, 0);

            f.set_chars({ R"(@@__@@)",
                          R"(@( ')')",
                          R"(@@@@@@)",});
            f.set_foreground_colors( { { a, a, g, g, a, a },
                                       { a, g, g, g, g, g },
                                       { a, a, a, a, a, a } } );
            f.set_background_colors( { { w, w, a, a, w, w },
                                       { w, w, w, w, w, w },
                                       { w, w, w, w, w, w } } );

            current_frame = f;

            respect_light_sources = false;

        }

};


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
};

class Normal_Test: public Sprite
{
    public:
        Normal_Test() {
            x_position = 0;
            y_position = 0;
            z_position = 0;

            height = 8;
            width = 16;

            respect_light_sources = true;
            use_normal_mapping = true;

            Frame f = Frame(height, width);
            f.set_chars({ R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)",
                          R"(XXXXXXXXXXXXXXXX)" });

            Vector ul = Vector(-120, -120, 0);
            Vector ur = Vector(120, -120, 0);
            Vector dl = Vector(-120, 120, 0);
            Vector dr = Vector(120, 120, 0);

            f.set_normals({{ ul, ul, ul, ul, ur, ur, ur, ur, ul, ul, ul, ul, ur, ur, ur, ur },
                           { ul, ul, ul, ul, ur, ur, ur, ur, ul, ul, ul, ul, ur, ur, ur, ur },
                           { dl, dl, dl, dl, dr, dr, dr, dr, dl, dl, dl, dl, dr, dr, dr, dr },
                           { dl, dl, dl, dl, dr, dr, dr, dr, dl, dl, dl, dl, dr, dr, dr, dr },
                           { ul, ul, ul, ul, ur, ur, ur, ur, ul, ul, ul, ul, ur, ur, ur, ur },
                           { ul, ul, ul, ul, ur, ur, ur, ur, ul, ul, ul, ul, ur, ur, ur, ur },
                           { dl, dl, dl, dl, dr, dr, dr, dr, dl, dl, dl, dl, dr, dr, dr, dr },
                           { dl, dl, dl, dl, dr, dr, dr, dr, dl, dl, dl, dl, dr, dr, dr, dr }});

            current_frame = f;
        }
};

class ground1: public Sprite
{
    public:

        ground1() {
            x_position = 0;
            y_position = 0;
            z_position = 0;

            respect_light_sources = true;

            height = 15;
            width = 10000;

            Frame f = Frame(height, width);


            vector<string> char_vec;
            for (int h = 0; h < height; h++)
            {
                string str = "";

                for (int w = 0; w < width; w++)
                {
                    if (h == 3 || h == 5)
                    {
                        str += "_";
                    }
                    else if (h == 4)
                    {
                        str += " ";
                    }
                    else if (h == 1)
                    {
                        int num = rand() % 10;
                        if (num == 0)
                            str += "M";
                        else if (num == 1)
                            str += "M";
                        else
                            str += " ";
                    }
                    else
                    {
                        int num = rand() %10;
                        if (num == 0)
                            str += "M";
                        else
                            str += " ";
                    }

                }

                char_vec.push_back(str);
            }

            f.set_chars(char_vec);

            Color g = Color(22, 92, 18);
            Color t = Color(214, 194, 133);
            Color d = Color(36, 34, 6);

            vector<vector<Color>> fc_vec;
            for (int h = 0; h < height; h++)
            {
                vector<Color> row;
                for (int w = 0; w < width; w++)
                {
                    if (h == 3 || h == 5)
                        row.push_back(t);
                    else
                        row.push_back(g);
                }
                fc_vec.push_back(row);
            }
            f.set_foreground_colors(fc_vec);


            g = Color(105, 181, 130);
            t = Color(214, 194, 133);
            //t = Color(130, 118, 82);

            vector<vector<Color>> bc_vec;
            for (int h = 0; h < height; h++)
            {
                vector<Color> row;
                for (int w = 0; w < width; w++)
                {
                    if (h >= 3 && h <= 5)
                        row.push_back(t);
                    else
                        row.push_back(g);
                }
                bc_vec.push_back(row);
            }
            f.set_background_colors(bc_vec);


            /*
            f.set_foreground_colors({{ g, g, g, g, g, g, g, g, g, g},
                                     { g, g, d, g, g, g, g, g, g, d},
                                     { d, d, d, d, d, d, d, d, d, d},
                                     { d, d, d, d, d, d, d, d, d, d},
                                     { d, d, d, d, d, d, d, d, d, d}});

            f.set_background_colors({{ g, g, g, g, g, g, g, g, g, g},
                                     { b, b, b, b, b, b, b, b, b, b},
                                     { b, b, b, b, b, b, b, b, b, b},
                                     { b, b, b, b, b, b, b, b, b, b},
                                     { b, b, b, b, b, b, b, b, b, b}});*/
            current_frame = f;
        }
};


void Person::animate()
{
    // Add time_diff to local counter

    long long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    long long time_since_last_run = now - last_run_time;

    long long frame_length_ms = 250;

    if (time_since_last_run > frame_length_ms)
    {
        while (time_since_last_run > frame_length_ms)
        {
            current_frame_index = (current_frame_index + 1) % 2;

            current_frame = frames.at(current_frame_index);

            time_since_last_run -= frame_length_ms;
        }

        last_run_time = now;
    }

}


int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}


int main()
{

    Engine engine;

/*
    Palm_tree tree;
    tree.move(0, 0, -10);
    Palm_tree tree2;
    tree2.move(0, 0, -12);
    Palm_tree tree3;
    tree3.move(0, 0, -16);
    Palm_tree tree4;
    tree4.move(150, 0, -1);
    Palm_tree tree5;
    tree5.move(200, 0, -1);
*/

    main_character person;
    //person.move(75, 16, 0);
    person.move(0, 0, -21);
    //tree.move(0, 0, -1);

    //Color_Test color_test;
    //color_test.move(0, 0, -1);

    //Palm_tree more_trees[100];
    //for (int i = 0; i < 100; i++)
    //    engine.add_sprite(&more_trees[i]);

    //ground1 g;
    //g.move(0, 22, -1);

    //engine.add_sprite(&g);


    //engine.add_sprite(&tree);
    //engine.add_sprite(&tree3);
    //engine.add_sprite(&tree4);
    //engine.add_sprite(&tree5);
    engine.add_sprite(make_shared<Sprite>(person));
    //engine.add_sprite(&tree2);
    //engine.add_sprite(&color_test);

    Point_Light p = Point_Light(Color(255, 255, 255), 0.95);
    //engine.add_light(&p);



    //Bars b;
    //b.move(-(b.get_width() / 2), -(b.get_height() / 2), -1);
    //engine.add_sprite(&b);


    //Normal_Test nt;
    //nt.move(-50, 0, -1);
    //engine.add_sprite(&nt);


    //////////////////////
    // GENERATE TV BARS //
    //////////////////////
    /*
    // Get window dimensions
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    Frame new_frame(size.ws_row, size.ws_col);

    int bar_width = (int)(size.ws_col / 7);
    int bar_height = (int)(size.ws_row * 0.66);

    // Color top bars
    */

    //////////////////////


/*


    chrono::microseconds time;

    move(0, 0);
    string s = "Testing, attention please.          ";
    waddstr(stdscr, s.c_str());

    // Refresh window
    wrefresh(stdscr);

    sleep(1);

    //engine.move_camera(0, 0, 10);

    int counter = 0;

    // TODO: MAKE SURE FRAME IS CORRECT SIZE FOR WINDOW
    int h, w;
    getmaxyx(stdscr, h, w);

    h = 55;
    w = 100;

    // Render new frame
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    Frame new_frame(size.ws_row, size.ws_col);
*/
    while (TRUE)
    {

        int c = getch();
        switch(c)
        {
            case 'w':
                //engine.move_camera(0, -5, 0);
                //person.move(0, -5, 0);
                p.move(0, -1, 0);
                break;

            case 'a':
                //engine.move_camera(-5, 0, 0);
                //person.move(-5, 0, 0);
                p.move(-1, 0, 0);
                break;

            case 's':
                //engine.move_camera(0, 5, 0);
                //person.move(0, 5, 0);
                p.move(0, 1, 0);
                break;

            case 'd':
                //engine.move_camera(5, 0, 0);
                //person.move(5, 0, 0);
                p.move(1, 0, 0);
                break;

            case 'q':
                p.move(0, 0, -1);
                break;

            case 'e':
                p.move(0, 0, 1);
                break;
        }

        //engine.move_camera(2, 0, 0);
        //person.move(2, 0, 0);

        // Tell every sprite to animate itself
        //engine.animate();

        // Before rendering, update frame size to match window size
        /*struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        new_frame.set_width(size.ws_col);
        new_frame.set_height(size.ws_row);
        */
        //engine.render_frame(&new_frame);

        // Display new frame
        //engine.display_frame(&new_frame);

        // Wait for the length of one frame
        // Test with 1FPS
        //usleep(10000);


//        if (counter++ > 10000)
//            break;
    }

}
