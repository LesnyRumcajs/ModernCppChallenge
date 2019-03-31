#pragma once

#include <chrono>
#include <utility>
#include <functional>

namespace cppchallenge::datetime {
    /**
     * Measures time execution of another function
     * @tparam Time
     * @tparam Clock
     * @tparam F
     * @tparam Args
     * @param f function to measure
     * @param args function's arguments
     * @return function execution time
     */
    template<typename Time = std::chrono::microseconds,
            typename Clock = std::chrono::high_resolution_clock,
            typename F, typename ... Args>
    static Time measure(F &&f, Args... args) {
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end - start);
    }
}