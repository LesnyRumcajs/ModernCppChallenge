#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/numerical_to_roman.h"

namespace {
    using namespace testing;

    TEST(NumericalToRomanTest, GivenZeroShouldReturnEmpty) {
        ASSERT_THAT(cppchallenge::math::numerical_to_roman(0), IsEmpty());
    }

    TEST(NumericalToRomanTest, Given1To10ShouldReturnRomanRepresentation) {
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(1), "I");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(2), "II");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(3), "III");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(4), "IV");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(5), "V");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(6), "VI");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(7), "VII");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(8), "VIII");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(9), "IX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(10), "X");
    }

    TEST(NumericalToRomanTest, Given11To100ShouldReturnRomanRepresentation) {
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(15), "XV");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(22), "XXII");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(39), "XXXIX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(49), "XLIX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(89), "LXXXIX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(90), "XC");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(95), "XCV");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(99), "XCIX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(100), "C");
    }

    TEST(NumericalToRomanTest, GivenAbove100ShouldReturnRomanRepresentation) {
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(132), "CXXXII");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(492), "CDXCII");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(999), "CMXCIX");
        ASSERT_EQ(cppchallenge::math::numerical_to_roman(2018), "MMXVIII");
    }
}