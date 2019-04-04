#include "timezone_meeting.h"

#include <boost/date_time/local_time/local_time.hpp>

namespace cppchallenge::datetime {
    std::vector<std::string> local_times(const boost::local_time::local_date_time &reference_datetime,
                                         const std::vector<TimeZone> &time_zones) {

        std::vector<std::string> result;
        for (const auto &time_zone : time_zones) {
            boost::local_time::time_zone_ptr zone(new boost::local_time::posix_time_zone(time_zone));
            result.emplace_back(reference_datetime.local_time_in(zone).to_string());
        }
        return result;
    }
}
