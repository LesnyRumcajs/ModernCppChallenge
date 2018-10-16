#include <gtest/gtest.h>

#include "../../src/math/greatest_common_divisor.h"

namespace {
    TEST(GreatestCommonDivisor, EqualsArguments) {
        EXPECT_EQ(cppchallenge::math::greatest_common_divisor(99,99), 99);
    }

    TEST(GreatestCommonDivisor, FirstArgumentIsPrime) {
        EXPECT_EQ(cppchallenge::math::greatest_common_divisor(13,99), 1);
    }

    TEST(GreatestCommonDivisor, FirstIsAMultipleOfSecond) {
        EXPECT_EQ(cppchallenge::math::greatest_common_divisor(11,99), 11);
    }

    TEST(GreatestCommonDivisor, LargeValue) {
        EXPECT_EQ(cppchallenge::math::greatest_common_divisor(624129,2061517), 18913);
    }
}