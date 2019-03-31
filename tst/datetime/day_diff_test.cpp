#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "../../src/datetime/date.h"

namespace {
    using namespace testing;
    using cppchallenge::datetime::Date;

    TEST(DayDiffTest, GivenSameDateShouldReturnZero) {
        Date date{2019, 3, 31};
       ASSERT_EQ(date.day_difference_with(date), 0);
    }

    TEST(DayDiffTest, GivenDiffBetweenOlderAndEarlierShouldReturnNegative) {
        Date date1{2019, 3, 1};
        Date date2{2019, 3, 2};
        ASSERT_EQ(date2.day_difference_with(date1), -1);
    }

    TEST(DayDiffTest, GivenDifferentDateShouldCorrectlyDiffDays) {

        ASSERT_EQ(Date(1990, 10, 04).day_difference_with(Date(2011, 10, 04)), 7670);
    }
}
