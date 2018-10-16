#include "greatest_common_divisor.h"

unsigned long cppchallenge::math::greatest_common_divisor(unsigned long first, unsigned long second) {
    if (0 == second) {
        return first;
    }

    return greatest_common_divisor(second, first % second);
}
