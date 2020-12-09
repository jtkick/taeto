// This file is a proof of concept for Taeto

using namespace std;

#include "Engine.h"
#include "Sprite.h"
#include "Frame.h"

#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <chrono>

int w_char = 119;
int a_char = 97;
int s_char = 115;
int d_char = 100;
int space_char = 32;






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
            f.set_chars({ R"(@@___@@)",
                          R"(@/ ..\@)",
                          R"(@\_U_/@)",
                          R"((__|__@)",
                          R"(@@@|@@))",
                          R"(@@_|_@@)",
                          R"(@@|@|@@)" });
            frames.push_back(f);
            
            f.set_chars({ R"(@@___@@)",
                          R"(@/.. \@)",
                          R"(@\_U_/@)",
                          R"(@__|__))",
                          R"((@@|@@@)",
                          R"(@@_|_@@)",
                          R"(@@|@|@@)" });
            frames.push_back(f);
                               
            //current_frame.set_chars(data[0]);
            
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
    
    Person person;
    //person.move(75, 16, 0);
    person.move(0, 0, -1);
    tree.move(0, 0, -1);
    
    engine.add_sprite(&tree);
    engine.add_sprite(&tree3);
    engine.add_sprite(&tree4);
    engine.add_sprite(&tree5);
    engine.add_sprite(&person);
    engine.add_sprite(&tree2);
    

    chrono::microseconds time;
   
    move(0, 0);
    string s = "Testing, attention please.          ";
    waddstr(stdscr, s.c_str());
        
    // Refresh window
    wrefresh(stdscr);
    
    sleep(1);
    
    //engine.move_camera(0, 0, 10);
 
    while (TRUE)
    {
    
        int c = getch();
        switch(c)
        {
            case 'w':
                engine.move_camera(0, -10, 0);
                person.move(0, -10, 0);
                break;
            
            case 'a':
                engine.move_camera(-10, 0, 0);
                person.move(-10, 0, 0);
                break;
                
            case 's':
                engine.move_camera(0, 10, 0);
                person.move(0, 10, 0);
                break;
                
            case 'd':
                engine.move_camera(10, 0, 0);
                person.move(10, 0, 0);
                break;
        }
        
        //engine.move_camera(2, 0, 0);
        //person.move(2, 0, 0);
    
        // Tell every sprite to animate itself
        engine.animate();
        
        // Render new frame
        Frame new_frame = engine.render_frame();
        
        // Display new frame
        engine.display_frame(new_frame);
        
        // Wait for the length of one frame
        // Test with 1FPS
        usleep(33333);
    }

}
