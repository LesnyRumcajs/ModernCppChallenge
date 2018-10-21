#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/armstrong_numbers.h"

namespace {
    using namespace testing;

    TEST(SumOfDigitsTest, GivenZeroShouldReturnZero) {
        EXPECT_EQ(cppchallenge::math::sum_of_digits(0), 0);
    }

    TEST(SumOfDigitsTest, GivenOneDigitNumberShouldCalculateSumOfDigits) {
        EXPECT_EQ(cppchallenge::math::sum_of_digits(5), 5);
        EXPECT_EQ(cppchallenge::math::sum_of_digits(9), 9);
    }

    TEST(SumOfDigitsTest, GivenMultipleDigitNumberShouldCalculateSumOfDigits) {
        EXPECT_EQ(cppchallenge::math::sum_of_digits(55), 10);
        EXPECT_EQ(cppchallenge::math::sum_of_digits(666), 18);
        EXPECT_EQ(cppchallenge::math::sum_of_digits(1024), 7);
        EXPECT_EQ(cppchallenge::math::sum_of_digits(1000), 1);
        EXPECT_EQ(cppchallenge::math::sum_of_digits(999), 27);
    }

    TEST(NumberOfDigitsTest, GivenZeroShouldReturnOne) {
        EXPECT_EQ(cppchallenge::math::number_of_digits(0), 1);
    }

    TEST(NumberOfDigitsTest, GivenOneDigitShouldReturnOne) {
        EXPECT_EQ(cppchallenge::math::number_of_digits(1), 1);
    }

    TEST(NumberOfDigitsTest, GivenOMultipleDigitNumberShouldReturnNumberOfDigits) {
        EXPECT_EQ(cppchallenge::math::number_of_digits(9), 1);
        EXPECT_EQ(cppchallenge::math::number_of_digits(99), 2);
        EXPECT_EQ(cppchallenge::math::number_of_digits(1024), 4);
        EXPECT_EQ(cppchallenge::math::number_of_digits(1032124), 7);
    }

    TEST(GetArmstrongNumbersTest, GivenIncorrectLimitsShouldThrow) {
        ASSERT_THROW(cppchallenge::math::get_armstrong_numbers(2, 1), std::invalid_argument);
    }

    TEST(GetArmstrongNumbersTest, GivenCorrectLimitWithoutArmstrongNumbersShouldReturnEmpty) {
        ASSERT_THAT(cppchallenge::math::get_armstrong_numbers(10, 15), IsEmpty());
    }

    TEST(GetArmstrongNumbersTest, GivenCorrectLimitWithArmstrongNumbersShouldReturnArmstrongNumbers) {
        ASSERT_THAT(cppchallenge::math::get_armstrong_numbers(1, 10000), ElementsAre(
                1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634, 8208, 9474
        ));
    }
}