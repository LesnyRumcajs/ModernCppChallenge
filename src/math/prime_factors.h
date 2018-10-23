#pragma once

#include <vector>

namespace cppchallenge::math {
    using prime_factor = unsigned;
    using prime_factors = std::vector<prime_factor>;

    /**
     * Returns prime factors of a given number. For 0 and 1 returns an empty container.
     * @param number
     * @return prime factors
     */
    prime_factors get_prime_factors(prime_factor number);
}