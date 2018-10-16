#include <gtest/gtest.h>
#include "../../src/math/least_common_multiple.h"

namespace {
    TEST(LeastCommonMultiple, GivenZeroShouldReturnZero) {
        EXPECT_EQ(cppchallenge::math::least_common_multiple(1,0), 0);
        EXPECT_EQ(cppchallenge::math::least_common_multiple(0,1), 0);
        EXPECT_EQ(cppchallenge::math::least_common_multiple(0,0), 0);
    }

    TEST(LeastCommonMultiple, ShouldHandleBasicValues) {
        EXPECT_EQ(cppchallenge::math::least_common_multiple(4,6), 12);
        EXPECT_EQ(cppchallenge::math::least_common_multiple(21,6), 42);
    }
}
