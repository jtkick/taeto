#ifndef SYSTEMS_INPUT_SYSTEM_H_
#define SYSTEMS_INPUT_SYSTEM_H_

#include <memory>
#include <vector>

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

    // Polls any key the engine want to keep tabs on
    void poll_inputs();

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    // Keys engine will keep an eye on
    std::vector<key_entry> keys;
};

}   // namespace taeto

#endif  // SYSTEMS_INPUT_SYSTEM_H_
