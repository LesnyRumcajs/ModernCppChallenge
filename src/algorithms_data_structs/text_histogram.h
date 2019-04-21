#pragma once

#include <map>
#include <vector>
#include <string_view>
#include <algorithm>
#include <numeric>

namespace cppchallenge::algorithms_data_structs {
    using character = std::string_view::value_type;
    using histogram = std::vector<std::pair<character, float>>;

    /**
     * Creates histogram of a given text, ignoring all digits, whitespaces and non-word characters.
     */
    histogram create_histogram(std::string_view text) {
        std::map<character, size_t> frequency;

        auto character_count(0u);
        for (const auto &ch : text) {
            if (std::isalpha(ch)) {
                ++frequency[ch];
                ++character_count;
            }
        }

        histogram result;
        std::transform(frequency.begin(), frequency.end(), std::back_inserter(result), [character_count](const auto& el) {
            return std::make_pair(el.first, 1.0 * el.second / character_count);
        });

        std::sort(result.begin(), result.end(), [](const auto& el1, const auto& el2){
           return el1.second > el2.second;
        });

        return result;
    }
}
