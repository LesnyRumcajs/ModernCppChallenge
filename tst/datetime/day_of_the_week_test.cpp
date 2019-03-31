#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "../../src/datetime/date.h"

namespace {
    using namespace testing;
    using cppchallenge::datetime::Date;

    TEST(DayOfTheWeekTest, ShoulGiveCorrectWeekdays) {
        ASSERT_EQ(Date(2019,03,31).day_of_week(), 0);
        ASSERT_EQ(Date(2011,10,04).day_of_week(), 2);
    }

}
