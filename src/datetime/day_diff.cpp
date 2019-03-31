#include "day_diff.h"

#include <boost/date_time.hpp>

namespace cppchallenge::datetime {
    Date::Date(date_type year, date_type month, date_type day) : year(year), month(month), day(day) {}

    long Date::day_difference_with(const Date &other) const {
        boost::gregorian::date date1 {this->year, this->month, this->day};
        boost::gregorian::date date2 {other.year, other.month, other.day};

        boost::gregorian::date_duration duration = date2 - date1;

        return duration.days();
    }

}
