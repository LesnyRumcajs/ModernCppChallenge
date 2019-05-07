#pragma once

#include <vector>
#include <algorithm>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Generates permutations of a given collection
     */
    template<typename T, typename It>
    auto generate_permutations(It begin, It end) {
        if (begin == end) {
            return std::vector<T>{};
        }
        std::sort(begin, end);

        std::vector<T> result;
        do {
            result.push_back({begin, end});
        } while (std::next_permutation(begin, end));

        return result;
    }
}
