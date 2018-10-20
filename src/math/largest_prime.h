#pragma once

namespace cppchallenge::math {
    /**
     * Checks if a given number is a prime
     * @param candidate
     * @return true for a prime
     */
    bool is_prime(unsigned candidate);

    /**
     * Returns largest prime up to the given limit (and including it)
     * @param limit
     * @return largest prime
     */
    unsigned largest_prime(unsigned limit);
}