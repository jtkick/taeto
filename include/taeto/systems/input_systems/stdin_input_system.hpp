#ifndef SYSTEMS_INPUT_SYSTEMS_STDIN_INPUT_SYSTEM_HPP_
#define SYSTEMS_INPUT_SYSTEMS_STDIN_INPUT_SYSTEM_HPP_

#include "taeto/systems/input_systems/input_system.hpp"

namespace taeto
{

class StdinInputSystem: public InputSystem
{
public:
    StdinInputSystem();

    ~StdinInputSystem();

    // Polls any key the engine want to keep tabs on
    void poll_inputs();

    float key_state(int id);

private:
    std::map<int, float> key_states_ = { };
    std::map<int, int> key_presses_ = { };
};

}   // namespace taeto

#endif  // SYSTEMS_INPUT_SYSTEMS_STDIN_INPUT_SYSTEM_HPP_
