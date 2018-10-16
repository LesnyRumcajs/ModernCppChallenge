#include "sum_of_naturals.h"

unsigned long cppchallenge::math::sum_of_naturals_divisable(unsigned limit) {
    unsigned long result{};
    for (int i = 1; i <= limit; ++i) {
        if (i % 3 == 0 && i % 5 == 0) {
            result += i;
        }
    }

    return result;
}
