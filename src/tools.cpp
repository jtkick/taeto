#include "tools.hpp"

#include <chrono>

namespace taeto
{

std::chrono::milliseconds ms_since_epoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

}   // namespace taeto