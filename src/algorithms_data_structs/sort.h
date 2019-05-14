#pragma once

#include <type_traits>
#include <iterator>

namespace cppchallenge::algorithms_data_structs {
    namespace details {
        /**
         * Partition algorithm
         * @warning Uses naive pivot
         */
        template<typename It, typename Compare = std::less<>>
        It partition(It begin, It end, Compare compare = Compare()) {
            auto pivot = *begin;

            auto smaller_index = begin + 1;
            auto larger_index = end - 1;

            while (smaller_index <= larger_index) {
                while (smaller_index <= larger_index && compare(*smaller_index, pivot)) {
                    ++smaller_index;
                }

                while (smaller_index <= larger_index && !compare(*larger_index, pivot)) {
                    --larger_index;
                }

                if (smaller_index < larger_index) {
                    std::iter_swap(smaller_index, larger_index);
                }
            }

            std::iter_swap(smaller_index - 1, begin);

            return smaller_index - 1;
        }
    }

    /**
     * Quick sort algorithm
     */
    template<typename It, typename Compare = std::less<>>
    void quick_sort(It begin, It end, Compare compare = Compare()) {
        using iterator_category = typename std::iterator_traits<It>::iterator_category;
        static_assert(std::is_convertible_v<iterator_category, std::random_access_iterator_tag>,
                "Provided iterator is not random-access!");

        if (begin < end) {
            auto part = details::partition(begin, end, compare);
            quick_sort(begin, part, compare);
            quick_sort(std::next(part), end, compare);
        }
    }
}
