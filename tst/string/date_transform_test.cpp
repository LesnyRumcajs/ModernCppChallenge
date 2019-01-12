#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/string/date_transform.h"

namespace {
    using namespace cppchallenge::string;
    using namespace testing;
    using namespace std::string_literals;

    TEST(DateTransformTest, GivenEmptyInputShouldReturnEmptyString) {
        ASSERT_THAT(date_transform(""s), IsEmpty());
    }

    TEST(DateTransformTest, GivenInputWithoutValidDateShouldNotModify) {
        ASSERT_EQ(date_transform("test"s), "test");
        ASSERT_EQ(date_transform("11.01-2019"s), "11.01-2019");
        ASSERT_EQ(date_transform("11@01@2019"s), "11@01@2019");
    }

    TEST(DateTransformTest, GivenSingleDotDateShouldReturnCorrectFormat) {
        ASSERT_EQ(date_transform("11.01.2019"s), "2019-01-11"s);
    }

    TEST(DateTransformTest, GivenSingleDashDateShouldReturnCorrectFormat) {
        ASSERT_EQ(date_transform("11-01-2019"s), "2019-01-11"s);
    }

    TEST(DateTransformTest, GivenMultipleDatesShouldCorrectlyReplace) {
        ASSERT_EQ(date_transform("11-01-2019 is the day after 10.01.2019"s), "2019-01-11 is the day after 2019-01-10"s);
    }
}
