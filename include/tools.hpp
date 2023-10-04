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

/**
 * Calculates smoothstep value.
 */
double smoothstep(double x, double edge0 = 0.0f, double edge1 = 1.0f);


}   // namespace taeto

#endif  // TOOLS_HPP_
