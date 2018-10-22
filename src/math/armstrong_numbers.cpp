#include <cmath>
#include <stdexcept>
#include "armstrong_numbers.h"

cppchallenge::math::armstrong_numbers
cppchallenge::math::get_armstrong_numbers(cppchallenge::math::armstrong_number min,
                                          cppchallenge::math::armstrong_number max) {
    if (min >= max) throw std::invalid_argument("invalid limits");

    armstrong_numbers result;
    for (unsigned i = min; i <= max; ++i) {
        auto num = i;
        auto sum = 0u;
        auto digits = number_of_digits(num);

        while (num > 0u) {
            sum += static_cast<unsigned>(std::pow(num % 10, digits));
            num /= 10;
        }

        if (sum == i) {
            result.push_back(i);
        }
    }

    return result;
}

unsigned cppchallenge::math::sum_of_digits(unsigned number) {
    unsigned sum{};

    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

unsigned cppchallenge::math::number_of_digits(unsigned number) {
    if (number <= 1) return 1;

    return static_cast<unsigned>(std::ceil(std::log10(number)));
}
