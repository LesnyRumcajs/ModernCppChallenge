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
    bool is_valid_length(const PhoneNumber &phoneNumber);

    /**
     * Checks if a phone number starts with a given country code (phone number can include '+' prefix)
     */
    bool starts_with_code(const PhoneNumber &phoneNumber, const CountryCode &countryCode);

    /**
     * Filters phone numbers by the country code
     */
    PhoneNumbers filter_phone_numbers(PhoneNumbers phoneNumbers, const CountryCode &countryCode);
}
