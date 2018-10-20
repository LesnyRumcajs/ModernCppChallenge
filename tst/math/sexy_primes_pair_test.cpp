#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "../../src/math/sexy_prime_pairs.h"

namespace {
    TEST(GetPrimesTest, GiveZeroOrOneLimitShouldReturnNothing) {
        EXPECT_TRUE(cppchallenge::math::get_primes(0).empty());
        EXPECT_TRUE(cppchallenge::math::get_primes(1).empty());
    }

    TEST(GetPrimesTest, GivenCorrectLimitShouldReturnPrimes) {
        auto result = cppchallenge::math::get_primes(10);
        ASSERT_THAT(result, testing::ElementsAre(2, 3, 5, 7));
    }

    TEST(GetPrimesTest, GivenCorrectLimitShouldReturnPrimesWithLimitIncluded) {
        auto result = cppchallenge::math::get_primes(11);
        ASSERT_THAT(result, testing::ElementsAre(2, 3, 5, 7, 11));
    }

    TEST(GetSexyPrimesTest, GivenZeroOrOneLimitShouldReturnNothing) {
        EXPECT_TRUE(cppchallenge::math::get_sexy_primes(0).empty());
        EXPECT_TRUE(cppchallenge::math::get_sexy_primes(1).empty());
    }

    TEST(GetSexyPrimesTest, GivenCorrectLimitShouldReturnSexyPrimes) {
        using namespace testing;
        auto result = cppchallenge::math::get_sexy_primes(20);
        ASSERT_THAT(result, ElementsAre(
                Pair(5, 11),
                Pair(7, 13),
                Pair(11, 17),
                Pair(13, 19)
        ));
    }

    TEST(GetSexyPrimesTest, GivenCorrectLimitShouldReturnSexyPrimesLimitIncluded) {
        using namespace testing;
        auto result = cppchallenge::math::get_sexy_primes(19);
        ASSERT_THAT(result, ElementsAre(
                Pair(5, 11),
                Pair(7, 13),
                Pair(11, 17),
                Pair(13, 19)
        ));
    }
}