#pragma once

#include <string>
#include <optional>
#include <regex>

namespace cppchallenge::string {
    /**
     * Parts of URI, decomposed.
     */
    struct uri {
        std::string protocol;
        std::string domain;
        std::optional<int> port;
        std::optional<std::string> path;
        std::optional<std::string> query;
        std::optional<std::string> fragment;
    };

    /**
     * Decomposes input URI into specific parts
     * @param input
     * @return decomposed URI
     */
    std::optional<uri> parse_uri(const std::string& input) {
        static const std::regex PARSE_REGEX(R"(^(\w+):\/{2}([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");
        std::smatch matches;

        if (std::regex_match(input, matches, PARSE_REGEX) && matches[1].matched && matches[2].matched) {
            uri parts;
            parts.protocol = matches[1];
            parts.domain = matches[2];

            if (matches[3].matched) {
                parts.port = std::stoi(matches[4]);
            }

            if (matches[5].matched) {
                parts.path = matches[5];
            }

            if (matches[7].matched) {
                parts.query = matches[7];
            }

            if (matches[9].matched) {
                parts.fragment = matches[9];
            }

            return parts;
        }

        return {};
    }
}
