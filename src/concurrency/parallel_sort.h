#pragma once

#include <functional>
#include <future>

#include "../algorithms_data_structs/sort.h"

namespace cppchallenge::concurrency {
    /**
     * Quick sort algorithm, parallel flavour using async.
     */
    template<typename It, typename Compare = std::less<>>
    void parallel_quick_sort(It begin, It end, Compare compare = Compare()) {
        using iterator_category = typename std::iterator_traits<It>::iterator_category;
        static_assert(std::is_convertible_v<iterator_category, std::random_access_iterator_tag>,
                      "Provided iterator is not random-access!");

        if (begin < end) {
            auto part = algorithms_data_structs::details::partition(begin, end, compare);

            auto first_part = std::async(std::launch::async, [begin, part, compare]() {
                parallel_quick_sort(begin, part, compare);
            });
            auto second_part = std::async(std::launch::async, [part, end, compare]() {
                parallel_quick_sort(std::next(part), end, compare);
            });
        }
    }
}
