#include "taeto/systems/input_system.hpp"

#include <memory>

#include <SFML/Window/Keyboard.hpp>

namespace taeto
{

InputSystem::InputSystem()
{
    // TODO: MAKE THIS VARIABLE
    buttons_ = {{0, sf::Keyboard::Key::A},
                {1, sf::Keyboard::Key::W},
                {2, sf::Keyboard::Key::S},
                {3, sf::Keyboard::Key::D},
                {4, sf::Keyboard::Key::Q},
                {5, sf::Keyboard::Key::E},
                {6, sf::Keyboard::Key::Space}};

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
