#include <cmath>
#include "prime_factors.h"

cppchallenge::math::prime_factors cppchallenge::math::get_prime_factors(prime_factor number) {
    if (number == 0) return {};
    prime_factors result;

    static const prime_factor EVEN_FACTOR = 2;
    while (number % EVEN_FACTOR == 0) {
        result.emplace_back(EVEN_FACTOR);
        number /= EVEN_FACTOR;
    }

    for (prime_factor i{3}; i <= std::sqrt(number); i += 2) {
        if (number % i == 0) {
            result.push_back(i);
            number /= i;
        }
    }

    if (number > 1) {
        result.push_back(number);
    }

    return result;
}
