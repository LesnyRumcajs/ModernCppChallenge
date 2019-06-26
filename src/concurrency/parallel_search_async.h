#pragma once

#include <utility>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

namespace cppchallenge::concurrency {
    namespace details {
        template<typename Iterator, typename F>
        auto parallel_async_process(Iterator begin, Iterator end, F &&f) {
            using iterator_value_type = typename std::iterator_traits<Iterator>::value_type;
            static const auto PARALLEL_THRESHOLD = 10'000;
            auto container_size = end - begin;

            if (container_size == 0) {
                throw std::invalid_argument("Empty container!");
            } else if (container_size <= PARALLEL_THRESHOLD) {
                return std::forward<F>(f)(begin, end);
            }

            const auto PARALLEL_TASKS_COUNT = std::thread::hardware_concurrency();

            auto tasks = std::vector<std::future<iterator_value_type>>{};

            auto first = begin;
            auto last = first;

            container_size /= PARALLEL_TASKS_COUNT;

            for (auto i{0u}; i < PARALLEL_TASKS_COUNT; ++i) {
                first = last;

                if (i == PARALLEL_TASKS_COUNT - 1) {
                    last = end;
                } else {
                    std::advance(last, container_size);
                }

                tasks.emplace_back(std::async(std::launch::async, [first, last, &f]() {
                    return std::forward<F>(f)(first, last);
                }));
            }

            auto candidates = std::vector<iterator_value_type>{};
            for (auto &task : tasks) candidates.emplace_back(task.get());

            return std::forward<F>(f)(candidates.begin(), candidates.end());
        }
    }

    /**
     * Find the largest element in a given container
     */
    template<typename Iterator>
    auto parallel_async_max(Iterator begin, Iterator end) {
        return details::parallel_async_process(begin, end, [](const auto begin, const auto end) {
            return *std::max_element(begin, end);
        });
    }

    /**
     * Finds the smallest element in a given container
     */
    template<typename Iterator>
    auto parallel_async_min(Iterator begin, Iterator end) {
        return details::parallel_async_process(begin, end, [](const auto begin, const auto end) {
            return *std::min_element(begin, end);
        });
    }

    /**
     * Finds the sum of elements a given container
     */
    template<typename Iterator>
    auto parallel_async_sum(Iterator begin, Iterator end) {
        return details::parallel_async_process(begin, end, [](const auto begin, const auto end) {
            return std::accumulate(begin, end, 0);
        });
    }
}
