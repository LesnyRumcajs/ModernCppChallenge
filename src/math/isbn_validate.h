#pragma once

#include <string>

namespace cppchallenge::math {
    /**
     * Checks if a given string is a valid isbn10
     * @param isbn
     * @return true if valid, false otherwise
     */
    bool is_valid_isbn_10(const std::string &isbn);
}
