#pragma once

namespace cppchallenge::lang {
    /**
     * Adds values to the container
     * @tparam Container
     * @tparam Values
     * @param container
     * @param args
     */
    template<typename Container, typename ...Values>
    void push_values(Container &container, Values &&... args) {
        (container.push_back(args), ...);
    }
}
