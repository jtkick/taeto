#include "palm_tree.h"

#include <memory>
#include <vector>

#include "components/color.h"
#include "components/frame.h"

namespace taeto
{

PalmTree::PalmTree()
{
    // Default position to the origin
    x_position = 0;
    y_position = 0;
    z_position = 0;

    // Set frame details
    height = 22;
    width = 45;
    std::vector<string> default_chars = {
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

    default_frame = taeto::Frame(22, 45);

    default_frame.set_chars(default_chars);

    respect_light_sources = true;

    // Trunk color
    taeto::Color t = Color(170, 166, 161);
    // Leaf color
    taeto::Color l = Color(105, 181, 130);
    // Fully alpha
    taeto::Color a = Color(0, 0, 0, 0);

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

shared_ptr<taeto::Frame> PalmTree::get_current_frame()
{
    return std::make_shared<taeto::Frame>(default_frame);
}

}   // namespace taeto
