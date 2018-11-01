#pragma once

#include <algorithm>

namespace cppchallenge::lang {
    /**
     * Checks if a container contains a given value
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename T>
    bool contains(const Container &container, T &&value) {
        return std::find(container.begin(), container.end(), value) != container.end();
    }

    /**
     * Checks if container contains any of the given values
     * @tparam Container
     * @tparam T
     * @param container
     * @param values
     * @return
     */
    template<typename Container, typename... T>
    bool contains_any(const Container &container, T &&... values) {
        return (... || contains(container, values));
    }

    /**
     * Checks if container contains all of the given values
     * @tparam Container
     * @tparam T
     * @param container
     * @param values
     * @return
     */
    template<typename Container, typename... T>
    bool contains_all(const Container &container, T &&... values) {
        return (... && contains(container, values));
    }

    /**
     * Checks if container contains none of the given values
     * @tparam Container
     * @tparam T
     * @param container
     * @param values
     * @return
     */
    template<typename Container, typename... T>
    bool contains_none(const Container &container, T &&... values) {
        return !contains_any(container, std::forward<T>(values)...);
    }
}
