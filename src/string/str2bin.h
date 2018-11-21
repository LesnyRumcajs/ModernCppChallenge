#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <charconv>

namespace cppchallenge::string {
    /**
     * Converts hex-encoded string to raw-bytes vector
     * @tparam T container element type
     * @param str hex encoded string
     * @return raw-bytes vector
     */
    template<typename T = uint8_t>
    std::vector<T> str2bin(const std::string &str) {
        if (str.length() % 2) {
            throw std::invalid_argument("Invalid hex-encoded string");
        }

        static const size_t CHARS_PER_NUM = 2;
        std::vector<T> result(str.size() / CHARS_PER_NUM);

        std::for_each(result.begin(), result.end(), [&str, idx = 0](auto &el) mutable {
            auto conversion_result= std::from_chars<T>(str.data() + idx,
                                             str.data() + idx + CHARS_PER_NUM,
                                             el, 16);

            if (conversion_result.ptr != str.data() + idx + CHARS_PER_NUM) {
                throw std::invalid_argument("Invalid hex character");
            }

            idx += CHARS_PER_NUM;
        });
        return result;
    }
}
