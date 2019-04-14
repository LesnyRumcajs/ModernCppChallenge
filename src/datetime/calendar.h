#pragma once

#include "date.h"

#include <boost/date_time.hpp>
#include <sstream>

namespace cppchallenge::datetime {
        /**
         * Prints the specified month calendar to out param
         * @param year
         * @param month
         * @param out
         */
        void print_calendar(uint16_t year, uint16_t month, std::ostream& out);
}
