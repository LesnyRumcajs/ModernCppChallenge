#include "least_common_multiple.h"
#include "greatest_common_divisor.h"

unsigned long cppchallenge::math::least_common_multiple(unsigned long first, unsigned long second) {
    if (0 == first || 0 == second) return 0;

    // division before mutliplication to avoid possible overflows
    return first / greatest_common_divisor(first, second) * second;
}
