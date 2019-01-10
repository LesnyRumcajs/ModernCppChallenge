#pragma once

#include <string_view>
#include <regex>

namespace cppchallenge::string {
    /**
     * Validates if a given text is a valid plate (format LLL-LLL DDD or LLL-LLL DDDD)
     * @param plate
     * @return true if valid plate, false otherwise
     */
    bool validate_plate(const std::string_view plate) {
        static const std::regex PLATE_RGX("^[A-Z]{3}-[A-Z]{3} \\d{3,4}$");
        return std::regex_match(plate.data(), PLATE_RGX);
    }

    /**
     * Returns all valid plates from a given text
     * @param input
     * @return collection of valid plates
     */
    std::vector<std::string> extract_plate(const std::string& input) {
        static const std::regex PLATE_RGX("([A-Z]{3}-[A-Z]{3} \\d{3,4})");

        std::vector<std::string> plates;
        std::copy( std::sregex_token_iterator(input.begin(), input.end(), PLATE_RGX, 1),
              std::sregex_token_iterator(),
              std::back_inserter(plates));

        return plates;
    }
}
