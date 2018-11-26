#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <list>

#include "../../src/string/tokenize.h"

namespace {
    using namespace cppchallenge::string;
    using namespace testing;
    using namespace std::string_literals;

    TEST(TokenizeTest, GivenNoDelimitersShouldNotSplit) {
        ASSERT_THAT(tokenize("test"s, ""s), ElementsAre("test"));
    }

    TEST(TokenizeTest, GivenEmptyStringShouldReturnEmptyVector) {
        ASSERT_THAT(tokenize(""s, ","s), IsEmpty());
    }

    TEST(TokenizeTest, GivenNonExistentDelimiterShouldNotSplit) {
        ASSERT_THAT(tokenize("this.is.a.test"s, " "s), ElementsAre("this.is.a.test"s));
    }

    TEST(TokenizeTest, GivenMultipleDelimitersInARowShouldNotIncludeEmptyElements) {
        ASSERT_THAT(tokenize("test,,fox"s, ","s), ElementsAre("test", "fox"));
    }

    TEST(TokenizeTest, GivenSingleDelimiterShouldCorrectlySplit) {
        ASSERT_THAT(tokenize("this is a sample"s, " "s), ElementsAre("this", "is", "a", "sample"));
    }

    TEST(TokenizeTest, GivenMultipleDelimitersShouldCorrectlySplit) {
        ASSERT_THAT(tokenize("this,is a.sample"s, ",. "s), ElementsAre("this", "is", "a", "sample"));
    }
}