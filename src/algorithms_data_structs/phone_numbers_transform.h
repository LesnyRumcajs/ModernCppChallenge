#pragma once

#include <string_view>
#include <algorithm>
#include <string>
#include <cctype>


namespace cppchallenge::algorithms_data_structs {
    /**
     * Transforms a single phone number to include country code in a unified format excluding whitespaces.
     */
    std::string phone_number_transform(std::string phoneNumber, std::string_view countryCode);

    /**
     * Transforms phone list to include country code in a unified format excluding whitespaces.
     */
    template<class It>
    void phone_numbers_transform(It begin, It end, std::string_view countryCode) {
        std::transform(begin, end, begin, [&countryCode](auto &el) {
            return phone_number_transform(std::move(el), countryCode);
        });
    }


}
