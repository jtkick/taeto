 #include "taeto/systems/input_systems/stdin_input_system.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <unordered_set>

#include <cctype>
#include <vector>


namespace taeto
{

StdinInputSystem::StdinInputSystem()
{
    // For fast input with no delays, turn off canonical mode
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

StdinInputSystem::~StdinInputSystem()
{
    // Re-enable canonical mode
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void StdinInputSystem::poll_inputs()
{
    // std::vector<sf::Keyboard::Key> keys = {
    //     sf::Keyboard::Key::W,
    //     sf::Keyboard::Key::A,
    //     sf::Keyboard::Key::S,
    //     sf::Keyboard::Key::D
    // };

    // for (const auto& key : keys)
    //     key_states_[(int)key] = static_cast<float>(sf::Keyboard::isKeyPressed(key));

    for (const auto& key : key_states_)
        key_states_[key.first] = 0.0;

    char c;
    fd_set set;
    struct timeval timeout = {0, 0};
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) > 0)
        while (read(STDIN_FILENO, &c, 0) > 0)
            key_states_[c] = 1.0;
}

float StdinInputSystem::key_state(int id)
{
    auto it = key_states_.find(id);
    if (it != key_states_.end())
        return it->second;
    throw std::invalid_argument("Not a valid ID.");
}

}   // namespace taeto
