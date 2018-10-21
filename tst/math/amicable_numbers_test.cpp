#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/amicable_numbers.h"

namespace {
    using namespace testing;

    TEST(GetAmicableNumbersTest, GivenZeroShouldReturnEmptyVector) {
        ASSERT_THAT(cppchallenge::math::get_amicable_numbers(0), IsEmpty());
    }

    TEST(GetAmicableNumbersTest, GivenPositiveAboveThresholdShouldReturnAmicableNumbers) {
        ASSERT_THAT(cppchallenge::math::get_amicable_numbers(220), ElementsAre(Pair(220, 284)));
        ASSERT_THAT(cppchallenge::math::get_amicable_numbers(3000), ElementsAre(
                Pair(220, 284),
                Pair(1184, 1210),
                Pair(2620, 2924)
        ));
    }
}
