#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/gray_code.h"

namespace {
    using namespace testing;

    TEST(Dec2BinaryTest, ShouldCorrectlyConvertDecToBinary) {
        ASSERT_EQ(cppchallenge::math::dec2binary(0), "00000000");
        ASSERT_EQ(cppchallenge::math::dec2binary(0b0101010), "00101010");
        ASSERT_EQ(cppchallenge::math::dec2binary(0b11111111), "11111111");
        ASSERT_EQ(cppchallenge::math::dec2binary(0b11001100), "11001100");
    }

    TEST(Dec2GrayTest, ShouldCorrectlyConvertDecToGray) {
        ASSERT_EQ(cppchallenge::math::dec2gray(0), "00000000");
        ASSERT_EQ(cppchallenge::math::dec2gray(1), "00000001");
        ASSERT_EQ(cppchallenge::math::dec2gray(15), "00001000");
        ASSERT_EQ(cppchallenge::math::dec2gray(42), "00111111");
    }

    TEST(Gray2DecTest, ShouldCorrectlyConvertGrayToDec) {
        ASSERT_EQ(cppchallenge::math::gray2dec("00000000"), 0);
        ASSERT_EQ(cppchallenge::math::gray2dec("00000001"), 1);
        ASSERT_EQ(cppchallenge::math::gray2dec("00001000"), 15);
        ASSERT_EQ(cppchallenge::math::gray2dec("00111111"), 42);
    }
}