#pragma once

#include <type_traits>

namespace cppchallenge::lang {
    /**
     * Gets minimum element from a two
     * @tparam T type
     * @param first
     * @param second
     * @return minimum
     */
    template<typename T>
    T min(T first, T second) {
        return first < second ? first : second;
    }

    template<typename First, typename... Args>
    using are_same = std::conjunction<std::is_same<First, Args>...>;

    /**
     * Gets minimum element from a list of arguments
     * @tparam First first element type
     * @tparam Args rest of elements type
     * @param first
     * @param args
     * @return minimum
     */
    template<typename First, typename... Args, typename = std::enable_if<are_same<First, Args...>::value, void>>
    First min(First first, Args... args) {
        if (0 == sizeof...(args)) return first;
        return min(first, min(args...));
    }
}
