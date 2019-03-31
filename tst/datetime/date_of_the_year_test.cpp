
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "../../src/datetime/date.h"

namespace {
    using namespace testing;
    using cppchallenge::datetime::Date;

    TEST(DayOfTheYearTest, ShoulGiveCorrectDays) {
        ASSERT_EQ(Date(2019,03,31).day_of_the_year(), 90);
        ASSERT_EQ(Date(2011,10,04).day_of_the_year(), 277);
    }

    TEST(DayOfTheYearTest, LastDayOfLeapYear) {
        ASSERT_EQ(Date(2016,12,31).day_of_the_year(), 366);
    }

    TEST(DayOfTheYearTest, LastDayOfNonLeapYear) {
        ASSERT_EQ(Date(2017,12,31).day_of_the_year(), 365);
    }
}
