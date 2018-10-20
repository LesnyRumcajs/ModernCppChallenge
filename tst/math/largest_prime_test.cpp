#include <gtest/gtest.h>
#include "../../src/math/largest_prime.h"

namespace {
    TEST(IsPrimeTest, ZeroIsNotAPrime) {
        EXPECT_FALSE(cppchallenge::math::is_prime(0));
    }

    TEST(IsPrimeTest, GivenPrimesShouldBeTrue) {
        std::vector<unsigned> non_primes = {3, 7, 13, 31};
        std::for_each(non_primes.begin(), non_primes.end(), [](auto non_prime) {
            EXPECT_TRUE(cppchallenge::math::is_prime(non_prime));
        });
    }

    TEST(IsPrimeTest, GivenNonPrimesShouldBeFalse) {
        std::vector<unsigned> non_primes = {4, 10, 15, 33};
        std::for_each(non_primes.begin(), non_primes.end(), [](auto non_prime) {
            EXPECT_FALSE(cppchallenge::math::is_prime(non_prime));
        });
    }

    TEST(LargestPrimeTest, GivenZeroShouldBeZero) {
        EXPECT_EQ(cppchallenge::math::largest_prime(0), 0);
    }

    TEST(LargestPrimeTest, GivenCorrectLimitShouldOutputCorrectPrime) {
        EXPECT_EQ(cppchallenge::math::largest_prime(4), 3);
        EXPECT_EQ(cppchallenge::math::largest_prime(15), 13);
        EXPECT_EQ(cppchallenge::math::largest_prime(60), 59);
    }

    TEST(LargestPrimeTest, GivenLimitEqualToPrimeShouldGiveLimit) {
        EXPECT_EQ(cppchallenge::math::largest_prime(31), 31);
    }
}