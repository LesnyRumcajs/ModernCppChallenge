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
        std::for_each(original.begin(), original.end(), [&result, toupcase = true](int ch) mutable {
            if (toupcase && std::isalpha(ch)) {
                toupcase = false;
                ch = std::toupper(ch);
            } else if (std::isspace(ch)) {
                toupcase = true;
            } else {
                ch = std::tolower(ch);
            }

            result.push_back(ch);
        });

        return result;
    }
}
