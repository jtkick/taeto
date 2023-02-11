#include "input_system.h"

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

    // I'm probably gonna regret this, but let's just hard-code which
    // keys the input system will poll for game input
    keys = { {'q', false},
             {'w', false},
             {'e', false},
             {'a', false},
             {'s', false},
             {'d', false},
             {' ', false}};
}

InputSystem::~InputSystem()
{

}

void InputSystem::poll_inputs()
{
    // Loop over each input keyboard key engine is watching
    for (int i = 0; i < keys.size(); i++)
    {
        key_entry &key = keys[i];

        sf::Keyboard::Key sf_key;
        switch (key.key)
        {
            case 'q':
                sf_key = sf::Keyboard::Q;
                break;

            case 'w':
                sf_key = sf::Keyboard::W;
                break;

            case 'e':
                sf_key = sf::Keyboard::E;
                break;

            case 'a':
                sf_key = sf::Keyboard::A;
                break;

            case 's':
                sf_key = sf::Keyboard::S;
                break;

            case 'd':
                sf_key = sf::Keyboard::D;
                break;

            case ' ':
                sf_key = sf::Keyboard::Space;
                break;
        }

        // Poll key
        bool key_pressed = sf::Keyboard::isKeyPressed(sf_key);

        // If key is different from last time
        if (key_pressed != key.pressed)
        {
            // Update entry
            key.pressed = key_pressed;
        }
    }
}

}   // namespace taeto
