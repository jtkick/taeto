#include "systems/input_system.hpp"

#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include "spdlog/spdlog.h"

namespace taeto
{

InputSystem::InputSystem()
{

}

InputSystem::InputSystem(std::shared_ptr<spdlog::logger> l)
{
    logger = l;

    // TODO: MAKE THIS VARIABLE
    buttons_ = {{0, sf::Keyboard::A},
                {1, sf::Keyboard::W},
                {2, sf::Keyboard::S},
                {3, sf::Keyboard::D},
                {4, sf::Keyboard::Q},
                {5, sf::Keyboard::E},
                {6, sf::Keyboard::Space}};

    mapped_buttons_ = {{0, std::make_shared<bool>(false)},
                       {1, std::make_shared<bool>(false)},
                       {2, std::make_shared<bool>(false)},
                       {3, std::make_shared<bool>(false)},
                       {4, std::make_shared<bool>(false)},
                       {5, std::make_shared<bool>(false)},
                       {6, std::make_shared<bool>(false)}};
}

InputSystem::~InputSystem()
{

}

std::shared_ptr<bool> InputSystem::get_button_reference(int id)
{
    return mapped_buttons_[id];
}

// int64_t InputSystem::input_value(int id = 0)
// {

// }

void InputSystem::poll_inputs()
{
    // New poll method
    for (auto const& [key, val] : buttons_)
        *(mapped_buttons_[key]) = sf::Keyboard::isKeyPressed(val);
}

}   // namespace taeto
