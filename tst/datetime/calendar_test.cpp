#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/datetime/calendar.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::datetime;

    TEST(CalendarTest, MonthBeginsAtMonday) {
        std::stringstream result;
        print_calendar(2019, 4, result);

        std::string expected = "Mon Tue Wed Thu Fri Sat Sun\n"
                               "  1   2   3   4   5   6   7 \n"
                               "  8   9  10  11  12  13  14 \n"
                               " 15  16  17  18  19  20  21 \n"
                               " 22  23  24  25  26  27  28 \n"
                               " 29  30 \n";

        ASSERT_EQ(result.str(), expected);
    }

    TEST(CalendarTest, MonthBeginsAtFriday) {
        std::stringstream result;
        print_calendar(2019, 3, result);

        std::string expected = "Mon Tue Wed Thu Fri Sat Sun\n"
                               "                  1   2   3 \n"
                               "  4   5   6   7   8   9  10 \n"
                               " 11  12  13  14  15  16  17 \n"
                               " 18  19  20  21  22  23  24 \n"
                               " 25  26  27  28  29  30  31 \n"
                               "\n";

        ASSERT_EQ(result.str(), expected);
    }

    TEST(CalendarTest, IncorrectMonthShouldThrow) {
        std::stringstream result_dummy;
        ASSERT_ANY_THROW(print_calendar(2019, 13, result_dummy));
    }
}
