#pragma once

#include <string>
#include <algorithm>

namespace cppchallenge::string {
    /**
     * Capitalizes the string (title case)
     * @param original input string
     * @return title case string
     */
    std::string capitalize(std::string_view original) {
        std::string result; result.reserve(original.size());
        std::transform(original.begin(), original.end(), std::back_inserter(result), [toupcase = true](int ch) mutable {
            if (toupcase && std::isalpha(ch)) {
                toupcase = false;
                return std::toupper(ch);
            } else if (std::isspace(ch)) {
                toupcase = true;
                return ch;
            }

            return std::tolower(ch);
        });

        return result;
    }
}
