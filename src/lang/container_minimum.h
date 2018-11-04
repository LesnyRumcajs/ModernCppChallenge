#pragma once

#include <type_traits>
#include <functional>

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
    template<typename First, typename... Args, typename = std::enable_if_t<are_same<First, Args...>::value>>
    First min(First first, Args... args) {
        int *p = new int[20];
        return min(first, min(args...));
    }

    /**
     * Gets minimum with a custom comparator (two arguments)
     * @tparam Comparator
     * @tparam T
     * @param comp comparator
     * @param first
     * @param second
     * @return
     */
    template<typename Comparator, typename T>
    T min(Comparator comp, T first, T second) {
        return comp(first, second) ? first : second;
    }

    /**
     * Gets minimim with a custom comparator (variable number of arguments)
     * @tparam Comparator
     * @tparam First
     * @tparam Args
     * @param comp comparator
     * @param first
     * @param args
     * @return
     */
    template<typename Comparator, typename First, typename... Args,
            typename = std::enable_if_t<are_same<First, Args...>::value>,
            typename = typename std::enable_if<std::is_convertible<Comparator,
                    std::function<bool(First, First)>>::value>::type>
    First min(Comparator comp, First first, Args... args) {
        return min(comp, first, min(comp, args...));
    }
}
