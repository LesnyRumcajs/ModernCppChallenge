#pragma once

#include <string>
#include <regex>

namespace cppchallenge::string {
    /**
     * Replaces date occurences in format DD-MM-YYYY or DD.MM.YYYY to YYYY-MM-DD
     * @param text
     * @return reformatted string
     */
    std::string date_transform(std::string_view text) {
        static const std::regex re{R"((\d{2})(-|\.)(\d{2})(\2)(\d{4}))"};
        return std::regex_replace(text.data(), re, "$5-$3-$1");
    }
}