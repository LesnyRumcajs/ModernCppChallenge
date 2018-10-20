#include <algorithm>
#include "sexy_prime_pairs.h"
#include "largest_prime.h"

cppchallenge::math::sexy_primes cppchallenge::math::get_sexy_primes(unsigned limit) {
    static const unsigned SEXY_FACTOR{6};

    auto primes = get_primes(limit);
    sexy_primes result;

    for (auto it = primes.begin(); it < primes.end(); ++it) {
        for (auto potential_match = it + 1;
             potential_match != primes.end() && *potential_match - *it <= SEXY_FACTOR;
             ++potential_match) {
            if (*it == *(potential_match) - SEXY_FACTOR) result.emplace_back(std::make_pair(*it, *potential_match));
        }

    }

    return result;
}

cppchallenge::math::primes cppchallenge::math::get_primes(unsigned limit) {
    std::vector<unsigned> result;
    for (int prime_candidate = 2; prime_candidate <= limit; ++prime_candidate) {
        if (cppchallenge::math::is_prime(prime_candidate)) {
            result.emplace_back(prime_candidate);
        }
    }

    return result;
}
