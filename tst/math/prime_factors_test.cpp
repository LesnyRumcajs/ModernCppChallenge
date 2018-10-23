#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/prime_factors.h"

namespace {
    using namespace testing;

    TEST(GetPrimeFactorsTest, GivenZeroOrOneShouldReturnEmpty) {
        ASSERT_THAT(cppchallenge::math::get_prime_factors(0), IsEmpty());
        ASSERT_THAT(cppchallenge::math::get_prime_factors(1), IsEmpty());
    }

    TEST(GetPrimeFactorsTest, GivenPrimeShouldReturnPrime) {
        ASSERT_THAT(cppchallenge::math::get_prime_factors(2), ElementsAre(2));
        ASSERT_THAT(cppchallenge::math::get_prime_factors(5), ElementsAre(5));
        ASSERT_THAT(cppchallenge::math::get_prime_factors(29), ElementsAre(29));
        ASSERT_THAT(cppchallenge::math::get_prime_factors(59), ElementsAre(59));
    }

    TEST(GetPrimeFactorsTest, GivenNonPrimeShouldReturnPrimeFactors) {
        ASSERT_THAT(cppchallenge::math::get_prime_factors(9), ElementsAre(3, 3));
        ASSERT_THAT(cppchallenge::math::get_prime_factors(18), ElementsAre(2, 3, 3));
        ASSERT_THAT(cppchallenge::math::get_prime_factors(39), ElementsAre(3, 13));
    }
}
