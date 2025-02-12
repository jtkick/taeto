 #include "taeto/systems/input_systems/sfml_input_system.hpp"

// #include <SFML2/SFML.h>
#include <cctype>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

namespace taeto
{

SFMLInputSystem::SFMLInputSystem()
{

}

SFMLInputSystem::~SFMLInputSystem()
{

}

void SFMLInputSystem::poll_inputs()
{
    std::vector<sf::Keyboard::Key> keys = {
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::D
    };

    for (const auto& key : keys)
        key_states_[(int)key] = static_cast<float>(sf::Keyboard::isKeyPressed(key));
}

float SFMLInputSystem::key_state(int id)
{
    id = std::toupper(static_cast<unsigned char>(id));
    id = (int)static_cast<sf::Keyboard::Key>(id - 'A');
    return key_states_[id];
}

int SFMLInputSystem::key_presses(int id)
{

}

}   // namespace taeto
