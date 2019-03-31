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
    };
}
