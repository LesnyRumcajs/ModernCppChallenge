#pragma once

#include <string>
#include <vector>

#include "boost/date_time/local_time/local_time.hpp"

namespace cppchallenge::datetime {
    using TimeZone = std::string;
    /**
     * Returns local time of each zone given reference time in format like "2019-Apr-04 17:22:00 GMT"
     * @param reference_datetime
     * @param time_zones
     * @return
     */
    std::vector<std::string> local_times(const boost::local_time::local_date_time& reference_datetime, const std::vector<TimeZone>& time_zones);
}
