#include "largest_prime.h"

unsigned cppchallenge::math::largest_prime(unsigned limit) {
    for (unsigned candidate = limit; candidate > 0; --candidate) {
        if (cppchallenge::math::is_prime(candidate)) return candidate;
    }
    return 0;
}

bool cppchallenge::math::is_prime(unsigned candidate) {
    if (candidate == 2 || candidate == 3) return true;
    if (candidate % 2 == 0 || candidate % 3 == 0) return false;

    for (unsigned i = 5, w = 2; i * i <= candidate; i += w, w = 6 - w) {
        if (candidate % i == 0) return false;
    }

    return true;
}
