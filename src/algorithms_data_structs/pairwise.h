#pragma once

#include <utility>
#include <vector>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Packs the collection into collection of pairs. If collection length is odd, discards the last one.
     */
    template<typename T>
    std::vector<std::pair<T,T>> to_pairs(const std::vector<T>& data) {
        std::vector<std::pair<T,T>> result;

        for (auto it = data.begin(); it + 1 < data.end(); it += 2) {
            result.emplace_back(std::make_pair(*it, *(it + 1)));
        }

        return result;
    }
}
