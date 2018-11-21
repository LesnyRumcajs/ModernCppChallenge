#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <list>

#include "../../src/string/str2bin.h"

namespace {
    using namespace cppchallenge::string;

    TEST(str2binTest, GivenEmptyStringShouldReturnEmptyVector) {
        ASSERT_TRUE(str2bin("").empty());
    }

    TEST(str2binTest, GivenOddLengthStringShouldThrow) {
        ASSERT_THROW(str2bin("1"), std::invalid_argument);
    }

    TEST(str2binTest, GivenInvalidCharacterShouldThrow) {
        ASSERT_THROW(str2bin("1Z"), std::invalid_argument);
        ASSERT_THROW(str2bin("UZ"), std::invalid_argument);
        ASSERT_THROW(str2bin("U1"), std::invalid_argument);
        ASSERT_THROW(str2bin("1111G1"), std::invalid_argument);
    }

    TEST(str2binTest, GivenCorrectHexEncodedStringShouldReturnBytes) {
        ASSERT_THAT(str2bin("12"), testing::ElementsAre(0x12));
        ASSERT_THAT(str2bin("010203"), testing::ElementsAre(0x01, 0x02, 0x03));
        ASSERT_THAT(str2bin("ABCDEF"), testing::ElementsAre(0xAB, 0xCD, 0xEF));
        ASSERT_THAT(str2bin("abcdef"), testing::ElementsAre(0xAB, 0xCD, 0xEF));
    }

    TEST(str2binTest, GivenCorrectHexEncodedStringShouldReturnBytesCaseMix) {
        ASSERT_THAT(str2bin("aBcDeF"), testing::ElementsAre(0xAB, 0xCD, 0xEF));
    }
}