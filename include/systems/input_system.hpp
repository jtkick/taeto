#ifndef SYSTEMS_INPUT_SYSTEM_H_
#define SYSTEMS_INPUT_SYSTEM_H_

#include <map>
#include <memory>
#include <vector>

#include <SFML/Window/Keyboard.hpp>
#include "spdlog/spdlog.h"

#include "systems/system.hpp"

// Types of entries in input table to be updated
struct key_entry { char key; bool pressed; };

namespace taeto
{

class InputSystem: public System
{
public:
    InputSystem();

    InputSystem(std::shared_ptr<spdlog::logger>);

    ~InputSystem();

    // Returns reference to an input button boolean
    std::shared_ptr<bool> get_button_reference(int);

    // Polls any key the engine want to keep tabs on
    void poll_inputs();

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Axes to watch
    std::map<int, int32_t> axes_ = { };

    // Buttons to watch
    std::map<int, sf::Keyboard::Key> buttons_ = { };
    std::map<int, std::shared_ptr<bool>> mapped_buttons_ = { };


};

}   // namespace taeto

#endif  // SYSTEMS_INPUT_SYSTEM_H_
