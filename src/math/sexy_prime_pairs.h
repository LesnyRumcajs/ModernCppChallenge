#pragma once

#include <utility>
#include <vector>

namespace cppchallenge::math {
    using sexy_primes = std::vector<std::pair<unsigned, unsigned>>;
    using primes = std::vector<unsigned>;

    /**
     * Returns "sexy primes", pairs of primes which differs by six (as from SEX!!!!, that's why!)
     * @param largest prime to include in search
     * @return sexy primes
     */
    sexy_primes get_sexy_primes(unsigned limit);

    /**
     * Returns primes up to the given limit
     * @param largest prime to include
     * @return primes
     */
    primes get_primes(unsigned limit);
}