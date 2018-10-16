#include "greatest_common_divisor.h"

unsigned cppchallenge::math::greatest_common_divisor(unsigned first, unsigned second) {
    if (0 == second) {
        return first;
    }

    return greatest_common_divisor(second, first % second);
}
