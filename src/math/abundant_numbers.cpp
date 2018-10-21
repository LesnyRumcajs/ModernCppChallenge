#include "abundant_numbers.h"

#include <cmath>
#include <numeric>
#include <stdexcept>

unsigned cppchallenge::math::calculate_abundance(unsigned number) {
    auto divisors = cppchallenge::math::get_proper_divisors(number);
    return std::accumulate(divisors.begin(), divisors.end(), 0u);
}

std::vector<unsigned> cppchallenge::math::get_proper_divisors(unsigned number) {
    std::vector<unsigned> result;

    for (auto divisor = static_cast<unsigned>(std::ceil(number / 2.0));
         divisor > 0;
         --divisor) {
        if (number % divisor == 0) {
            result.push_back(divisor);
        }
    }

    return result;
}

cppchallenge::math::abundant_numbers cppchallenge::math::get_abundant_numbers(unsigned limit) {
    abundant_numbers result;
    static const auto FIRST_ABUNDANT_NUMBER = 12u;
    for (int num = FIRST_ABUNDANT_NUMBER; num <= limit; ++num) {
        auto abundance = calculate_abundance(num);
        if (abundance > num) {
            result.push_back(std::make_pair(num, abundance));
        }
    }

    return result;
}
