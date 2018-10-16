#include <gtest/gtest.h>
#include "../../src/math/sum_of_naturals.h"

namespace {
    TEST(SumOfNaturalsTest, Zero) {
        EXPECT_EQ(cppchallenge::math::sum_of_naturals_divisable(0), 0);
    }

    TEST(SumOfNaturalsTest, NoDivisables) {
        EXPECT_EQ(cppchallenge::math::sum_of_naturals_divisable(2), 0);
    }

    TEST(SumOfNaturalsTest, Divisables) {
        EXPECT_EQ(cppchallenge::math::sum_of_naturals_divisable(30), 225);
    }
}
