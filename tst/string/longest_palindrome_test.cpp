#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/string/longest_palindrome.h"

namespace {
    using namespace cppchallenge::string;
    using namespace testing;
    using namespace std::string_literals;

    TEST(LongestPalindromeTest, GivenNoTextShouldReturnEmptyString) {
        ASSERT_THAT(longest_palindrome(""s), IsEmpty());
    }

    TEST(LongestPalindromeTest, GivenSingleCharacterShouldReturnThisCharacter) {
        ASSERT_EQ(longest_palindrome("p"s), "p"s);
    }

    TEST(LongestPalindromeTest, GivenWholeTextOddLengthPalindromeShouldReturnText) {
        ASSERT_EQ(longest_palindrome("level"), "level");
    }

    TEST(LongestPalindromeTest, GivenWholeTextEvenLengthPalindromeShouldReturnText) {
        ASSERT_EQ(longest_palindrome("leveevel"), "leveevel");
    }

    TEST(LongestPalindromeTest, GivenSingleCharacterPalindromeShouldReturnFirstCharacter) {
        ASSERT_EQ(longest_palindrome("abcdefgh"), "a");
    }

    TEST(LongestPalindromeTest, GivenLongTextShouldReturnLongestPalindrome) {
        ASSERT_EQ(longest_palindrome("sahararahnide"), "hararah");
    }

}
