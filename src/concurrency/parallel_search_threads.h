#pragma once

#include <utility>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>

namespace cppchallenge::concurrency {
    namespace details {
        template<typename Iterator, typename F>
        auto parallel_process(Iterator begin, Iterator end, F &&f) {
            static const auto PARALLEL_THRESHOLD = 10'000;
            auto container_size = end - begin;

            if (container_size == 0) {
                throw std::invalid_argument("Empty container!");
            } else if (container_size <= PARALLEL_THRESHOLD) {
                return std::forward<F>(f)(begin, end);
            }

            auto thread_count = std::thread::hardware_concurrency();

            auto threads = std::vector<std::thread>{};
            auto candidates = std::vector<typename std::iterator_traits<Iterator>::value_type>(thread_count);

            auto first = begin;
            auto last = first;

            container_size /= thread_count;

            for (auto i{0u}; i < thread_count; ++i) {
                first = last;

                if (i == thread_count - 1) {
                    last = end;
                } else {
                    std::advance(last, container_size);
                }

                threads.emplace_back([first, last, &f, &result = candidates[i]]() {
                    result = std::forward<F>(f)(first, last);
                });
            }

            for (auto &thread : threads) thread.join();

            return std::forward<F>(f)(candidates.begin(), candidates.end());
        }
    }

    /**
     * Find the largest element in a given container
     */
    template<typename Iterator>
    auto parallel_max(Iterator begin, Iterator end) {
        return details::parallel_process(begin, end, [](const auto begin, const auto end) {
            return *std::max_element(begin, end);
        });
    }

    /**
     * Finds the smallest element in a given container
     */
    template<typename Iterator>
    auto parallel_min(Iterator begin, Iterator end) {
        return details::parallel_process(begin, end, [](const auto begin, const auto end) {
            return *std::min_element(begin, end);
        });
    }

    /**
     * Finds the sum of elements a given container
     */
    template<typename Iterator>
    auto parallel_sum(Iterator begin, Iterator end) {
        return details::parallel_process(begin, end, [](const auto begin, const auto end) {
            return std::accumulate(begin, end, 0);
        });
    }
}
