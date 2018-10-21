#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/abundant_numbers.h"

namespace {
    using namespace testing;

    TEST(GetProperDivisorsTest, GivenZeroShouldReturnEmptyVector) {
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(0), IsEmpty());
    }

    TEST(GetProperDivisorsTest, GivenPrimeShouldReturnOnlyOne) {
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(13), ElementsAre(1));
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(31), ElementsAre(1));
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(3), ElementsAre(1));
    }

    TEST(GetProperDivisorsTest, GivenCorrectLimitShouldReturnProperDivisors) {
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(1), ElementsAre(1));
        ASSERT_THAT(cppchallenge::math::get_proper_divisors(12), UnorderedElementsAre(1, 2, 3, 4, 6));
    }

    TEST(CalculateAbundanceTest, GivenZeroShouldReturnZero) {
        EXPECT_EQ(cppchallenge::math::calculate_abundance(0), 0);
    }

    TEST(CalculateAbundanceTest, GivenPositiveNumbersShouldCorrectlyCalculateAbundance) {
        EXPECT_EQ(cppchallenge::math::calculate_abundance(1), 1);
        EXPECT_EQ(cppchallenge::math::calculate_abundance(6), 6);
        EXPECT_EQ(cppchallenge::math::calculate_abundance(12), 16);
    }

    TEST(GetAbundantNumbersTest, GivenZeroLimitShouldReturnEmptyVector) {
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(0), IsEmpty());
    }

    TEST(GetAbundantNumbersTest, GivenPositiveLimitBelowTwelveShouldReturnEmptyVector) {
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(5), IsEmpty());
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(11), IsEmpty());
    }

    TEST(GetAbundantNumbersTest, GivenLimitTwelveShouldReturnTwelveWithAbundance) {
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(12), ElementsAre(Pair(12, 16)));
    }

    TEST(GetAbundantNumbersTest, GivenPositiveLimitAboveTwelveShouldReturnAbundantNumbers) {
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(19), ElementsAre(
                Pair(12, 16),
                Pair(18, 21)
        ));
        ASSERT_THAT(cppchallenge::math::get_abundant_numbers(24), ElementsAre(
                Pair(12, 16),
                Pair(18, 21),
                Pair(20, 22),
                Pair(24, 36)
        ));
    }
}
