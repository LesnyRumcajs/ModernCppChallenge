#include "date.h"

#include <boost/date_time.hpp>

namespace cppchallenge::datetime {
    Date::Date(date_type year, date_type month, date_type day) : year(year), month(month), day(day) {}

    long Date::day_difference_with(const Date &other) const {
        boost::gregorian::date date1 {this->year, this->month, this->day};
        boost::gregorian::date date2 {other.year, other.month, other.day};

        boost::gregorian::date_duration duration = date2 - date1;

        return duration.days();
    }

    Date::date_type Date::day_of_week() const {
        boost::gregorian::date date{this->year, this->month, this->day};
        return date.day_of_week();
    }

    Date::date_type Date::day_of_the_year() const {
        boost::gregorian::date date{this->year, this->month, this->day};
        return date.day_of_year();
    }

    Date::date_type Date::week_of_the_year() const {
        boost::gregorian::date date{this->year, this->month, this->day};
        return date.week_number();
    }
}

