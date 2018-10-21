#pragma once

#include <vector>

namespace cppchallenge::math {
    using abundant_number = std::pair<unsigned, unsigned>;
    using abundant_numbers = std::vector<abundant_number>;

    /**
     * Returns abundant numbers up to the given limit i.e. numbers for which the sum of its proper divisors is larger than the number itself
     * @param limit
     * @return
     */
    abundant_numbers get_abundant_numbers(unsigned limit);

    /**
     * Calculates abundance of a given number i.e. sum of its proper divisors
     * @param number
     * @return
     */
    unsigned calculate_abundance(unsigned number);

    /**
     * Returns proper divisors of a given number
     * @param number
     * @return  proper divisors
     */
    std::vector<unsigned> get_proper_divisors(unsigned number);

}
