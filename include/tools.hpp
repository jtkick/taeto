#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <chrono>

namespace taeto
{
    
/**
 * Returns number of milliseconds since UNIX epoch.
 *
 * @returns Number of milliseconds since UNIX epoch.
 */
std::chrono::milliseconds ms_since_epoch();

}   // namespace taeto

#endif  // TOOLS_HPP_
