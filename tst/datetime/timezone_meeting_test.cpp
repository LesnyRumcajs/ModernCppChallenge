#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/date_time/posix_time/ptime.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "../../src/datetime/timezone_meeting.h"

namespace {
    using namespace testing;
    using cppchallenge::datetime::local_times;
    using cppchallenge::datetime::TimeZone;

    boost::local_time::local_date_time create_reference_time() {
        std::string ts("2019-04-04 21:22:00.000");
        boost::posix_time::ptime pt(boost::posix_time::time_from_string(ts));
        boost::local_time::time_zone_ptr zone(
                new boost::local_time::posix_time_zone("UTC"));
        return boost::local_time::local_date_time(pt, zone);
    }

    TEST(TimezoneMeetingTest, GivenEmptyVectorShouldReturnNothing) {
        auto local_date_time = create_reference_time();
        ASSERT_THAT(local_times(local_date_time,{}), IsEmpty());
    }

    TEST(TimeZoneMeetingTest, GivenSingleElementShouldReturnLocalTime) {
        auto local_date_time = create_reference_time();
        auto result = local_times(local_date_time, {"GMT-4"});
        ASSERT_THAT(result, ElementsAre("2019-Apr-04 17:22:00 GMT"));
    }

    TEST(TimeZoneMeetingTest, GivenMultipleTimeZonesShouldReturnLocalTimes) {
        auto local_date_time = create_reference_time();
        auto result = local_times(local_date_time, {"GMT-4", "CEST", "GMT+9"});
        ASSERT_THAT(result, ElementsAre("2019-Apr-04 17:22:00 GMT", "2019-Apr-04 21:22:00 CEST", "2019-Apr-05 06:22:00 GMT"));
    }

}
