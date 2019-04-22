#include "phone_numbers_transform.h"

#include "phone_numbers_filter.h"

namespace cppchallenge::algorithms_data_structs {
    std::string phone_number_transform(std::string phoneNumber, std::string_view countryCode) {
        constexpr auto MIN_LEN = 10;
        if (phoneNumber.length() >= MIN_LEN && phoneNumber.front() != '+') {
            if (phoneNumber.front() == '0') {
                phoneNumber.front() = ' ';
            }

            phoneNumber.erase(std::remove_if(phoneNumber.begin(), phoneNumber.end(), [](const auto ch) {
                return std::isspace(ch);
            }), phoneNumber.end());

            if (!starts_with_code(phoneNumber, countryCode.data())) {
                phoneNumber.insert(0, countryCode.data());
            }

            if (phoneNumber.front() != '+') {
                phoneNumber.insert(0, "+");
            }
        }
        return phoneNumber;
    }
}
