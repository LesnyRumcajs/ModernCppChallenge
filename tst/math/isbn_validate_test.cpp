#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/math/isbn_validate.h"

namespace {
    TEST(IsbnValidateTest, GivenInvalidLengthStringShouldReturnFalse) {
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10(""));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("1231231"));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("3"));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("823190382091830921093821"));
    }

    TEST(IsbnValidateTest, GivenInvalidCharactersInStringShouldReturnFalse) {
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("111111111a"));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("111111111b"));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("c111111111"));
        ASSERT_FALSE(cppchallenge::math::is_valid_isbn_10("111111111e"));
    }

    TEST(IsbnValidateTest, GivenCorrectIsbnShouldReturnTrue) {
        ASSERT_TRUE(cppchallenge::math::is_valid_isbn_10("0306406152"));
        ASSERT_TRUE(cppchallenge::math::is_valid_isbn_10("8390021013"));
    }
}
