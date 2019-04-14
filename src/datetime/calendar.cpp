#include "calendar.h"

void cppchallenge::datetime::print_calendar(uint16_t year, uint16_t month, std::ostream &out) {
    out << "Mon Tue Wed Thu Fri Sat Sun\n";

    boost::gregorian::date first_day {year, month, 1};
    auto last_day = first_day.end_of_month();

    static const auto FILL_CHAR(' ');
    static const auto FILL_PER_DAY(3);

    auto current_weekday(1);
    for (auto prev_month_day(1); prev_month_day < first_day.day_of_week(); ++prev_month_day, ++current_weekday) {
        out << std::string(FILL_PER_DAY + 1, FILL_CHAR);
    }

    for (auto day(1); day <= last_day.day(); ++day, ++current_weekday) {
        out << std::right << std::setfill(FILL_CHAR) << std::setw(FILL_PER_DAY) << day << FILL_CHAR;

        if (current_weekday % 7 == 0) {
            out << '\n';
        }
    }
    out << '\n';
}
