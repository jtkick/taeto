#include "Sprite.h"

class Palm_tree: public Sprite
{
    public:

        Frame default_frame;

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

            default_frame = Frame(22, 45);
            
            default_frame.set_chars(default_chars);

            respect_light_sources = true;

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
    }

};

shared_ptr<Frame> Palm_Tree::get_current_frame()
{
    return make_shared<Frame>(default_frame);
}
