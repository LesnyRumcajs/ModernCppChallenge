#pragma once

namespace cppchallenge::datetime {
    struct Date {
        using date_type = short unsigned;

        date_type year;
        date_type month;
        date_type day;

        Date(date_type year, date_type month, date_type day);

        /**
         * Calculates difference in days between the object's date and the other one
         * @param other date to compare
         * @return  difference in days
         */
        long day_difference_with(const Date& other) const;

        /**
         * Returns the day of the week as a numeric type [0-6], with 0 being Sunday.
         */
        date_type day_of_week() const;

        /**
         * Returns the day of the year (can be 366 for leap years)
         * @return
         */
        date_type day_of_the_year() const;

        /**
         * Returns the calendar week of the year
         */
        date_type week_of_the_year() const;
    };
}
