#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <list>

#include "../../src/string/capitalize.h"

namespace {
    using namespace cppchallenge::string;

    TEST(CapitalizeTest, GivenEmptyStringShouldReturnEmptyString) {
        ASSERT_TRUE(capitalize("").empty());
    }

    TEST(CapitalizeTest, GivenSingleLowerCaseWordShouldCapitalize) {
        ASSERT_EQ(capitalize("test"), "Test");
    }

    TEST(CapitalizeTest, GivenSingleUpcaseWordShouldCapitalize) {
        ASSERT_EQ(capitalize("TEST"), "Test");
    }

    TEST(CapitalizeTest, GivenMultipleWordsShouldCorrectlyCapitalize) {
        ASSERT_EQ(capitalize("the c++ challenger"), "The C++ Challenger");
        ASSERT_EQ(capitalize("THIS IS an ExamplE, should wORk!"), "This Is An Example, Should Work!");
    }
}