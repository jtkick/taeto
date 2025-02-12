#ifndef SYSTEMS_INPUT_SYSTEMS_INPUT_SYSTEM_HPP_
#define SYSTEMS_INPUT_SYSTEMS_INPUT_SYSTEM_HPP_

#include <map>

#include "taeto/systems/system.hpp"

namespace taeto
{

class InputSystem: public System
{
protected:
    InputSystem() = default;

public:
    virtual ~InputSystem() = default;

    // Polls any key the engine want to keep tabs on
    virtual void poll_inputs() = 0;

    virtual float key_state(int id) = 0;

    virtual int key_presses(int id) = 0;
};

}   // namespace taeto

#endif  // SYSTEMS_INPUT_SYSTEMS_INPUT_SYSTEM_HPP_
