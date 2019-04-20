#pragma once

#include <vector>
#include <map>
#include <algorithm>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Returns a vector of most frequently occuring elements along with it's count.
     */
    template<typename T>
    std::vector<std::pair<T, size_t>> most_frequent(const std::vector<T> &data) {
        std::map<T, size_t> frequency;
        for (const auto &el : data) {
            frequency[el] += 1;
        }

        auto max_occurences = std::max_element(frequency.begin(), frequency.end(),
                                               [](const auto &lhs, const auto &rhs) {
                                                   return lhs.second < rhs.second;
                                               })->second;

        std::vector<std::pair<T, size_t>> result;
        std::copy_if(frequency.begin(), frequency.end(), std::back_inserter(result), [&max_occurences](const auto &el) {
            return el.second == max_occurences;
        });

        return result;
    }
}
