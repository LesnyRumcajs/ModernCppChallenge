#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace cppchallenge::lang {
    /**
     * Basic two dimensional array implementation. It is an adaptor over a continuous vector.
     * @tparam T value type
     * @tparam R rows count
     * @tparam C columns count
     */
    template<typename T, size_t R, size_t C>
    class BasicArray {
    public:
        using value_type = T;
        using iterator = value_type *;
        using const_iterator = const value_type *;

        BasicArray() : data(R * C) {}

        explicit BasicArray(std::initializer_list<T> list) : data(list) {}

        constexpr const T &at(size_t row, size_t column) const {
            return data.at(C * row + column);
        }

        constexpr const T &operator()(size_t row, size_t column) const {
            return at(row, column);
        }

        constexpr T &operator()(size_t row, size_t column) {
            if (row >= R || column >= C) throw std::out_of_range("tried to access index outside array bounds");
            return data[C * row + column];
        }

        /**
         * Checks if an array is empty (only when 0 rows or 0 columns)
         * @return
         */
        constexpr bool empty() const noexcept {
            return data.empty();
        }

        const_iterator begin() const {
            return data.data();
        }

        const_iterator end() const {
            return data.data() + data.size();
        }

        iterator begin() {
            return data.data();
        }

        iterator end() {
            return data.data() + data.size();
        }

        /**
         * Fills the array with a given value
         * @param value
         */
        void fill(const T &value) {
            std::fill(data.begin(), data.end(), value);
        }

    private:
        std::vector<T> data;
    };
}
