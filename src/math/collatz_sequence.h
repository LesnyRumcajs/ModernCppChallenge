#pragma once

#include <vector>

namespace cppchallenge::math {
    using collatz_number = unsigned;
    using collatz_numbers = std::vector<collatz_number>;

    /**
     * Creates a collatz sequence for a given number
     * @param number
     * @return collatz sequence
     */
    collatz_numbers create_collatz_sequence(collatz_number number);

    /**
     * Calculates the longest collatz sequence up to the given limit
     * @param limit
     * @return pair of length and starting number of the longest sequence
     */
    std::pair<collatz_number, collatz_number> longest_collatz_sequence(collatz_number limit);

}