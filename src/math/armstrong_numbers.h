#pragma once

#include <vector>

namespace cppchallenge::math {
    using armstrong_number = unsigned;
    using armstrong_numbers = std::vector<armstrong_number>;

    /**
     * Returns armstrong numbers (narcisstic numbers) i.e. numbers which are equal to the sum of their digits each
     * raised to the power of the number of digits.
     * @param min
     * @param max
     * @return armstrong numbers
     */
    armstrong_numbers get_armstrong_numbers(armstrong_number min, armstrong_number max);

    /**
     * Calculates the sum of digits of a given number
     * @param number
     * @return sum of digits
     */
    unsigned sum_of_digits(unsigned number);

    /**
     * Calculates the number of digits of a given number
     * @param number
     * @return number of digits
     */
    unsigned number_of_digits(unsigned number);
}