#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace cppchallenge::algorithms_data_structs {
    using PhoneNumber = std::string;
    using PhoneNumbers = std::vector<PhoneNumber>;
    using CountryCode = std::string;

    /**
     * Checks if a phone number has a valid length
     */
    bool is_valid_length(const PhoneNumber &phoneNumber) {
        constexpr auto MIN_PHONE_NUMBER_LEN = 11;
        return phoneNumber.size() >= MIN_PHONE_NUMBER_LEN;
    }

    /**
     * Checks if a phone number starts with a given country code (phone number can include '+' prefix)
     */
    bool starts_with_code(const PhoneNumber &phoneNumber, const CountryCode &countryCode) {
        auto countryCodePosition = phoneNumber.at(0) == '+' ? 1 : 0;
        return phoneNumber.substr(countryCodePosition, countryCode.length()) == countryCode;
    }

    /**
     * Filters phone numbers by the country code
     */
    PhoneNumbers filter_phone_numbers(PhoneNumbers phoneNumbers, const CountryCode &countryCode) {
        phoneNumbers.erase(std::remove_if(phoneNumbers.begin(), phoneNumbers.end(), [&countryCode](const auto &number) {
            return !is_valid_length(number) || !starts_with_code(number, countryCode);
        }), phoneNumbers.end());

        return phoneNumbers;
    }
}
