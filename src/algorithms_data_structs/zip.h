#pragma once

#include <utility>
#include <vector>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Zips collections into pairs. Discards excessive elements of the longest collection (if necessary)
     */
    template<typename T, typename U>
    std::vector<std::pair<T, U>> zip(const std::vector<T> &first, const std::vector<U> &second) {
        std::vector<std::pair<T, U>> result;

        auto first_it = first.begin();
        auto second_it = second.begin();

        while (first_it != first.end() && second_it != second.end()) {
            result.emplace_back(std::make_pair(*first_it, *second_it));
            ++first_it;
            ++second_it;
        }

        return result;
    }
}
