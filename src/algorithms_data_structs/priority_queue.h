#pragma once

#include <vector>
#include <functional>

namespace cppchallenge::algorithms_data_structs {

    /**
     * A priority queue that gives constant time lookup for the largest element
     * and logarithmic time complexity for adding and removing elements.
     * @tparam T element type
     * @tparam Compare comparator
     */
    template<typename T,
            typename Compare = std::less<typename std::vector<T>::value_type>>
    class PriorityQueue {
        using size_type = typename std::vector<T>::size_type;
        using value_type = typename std::vector<T>::value_type;
        using const_reference = typename std::vector<T>::const_reference;

    public:
        PriorityQueue() = default;

        PriorityQueue(std::initializer_list<T> list) : container(list) {
            std::make_heap(container.begin(), container.end());
        }

        bool empty() const noexcept {
            return container.empty();
        }

        size_type size() const noexcept {
            return container.size();
        }

        void push(const value_type &value) {
            container.push_back(value);
            std::push_heap(container.begin(), container.end(), comparer);
        }

        void emplace(value_type &&value) {
            container.emplace_back(value);
            std::push_heap(container.begin(), container.end(), comparer);

        }

        const_reference top() const {
            return container.front();
        }

        value_type pop() {
            std::pop_heap(container.begin(), container.end(), comparer);
            auto &&max = std::move(container.back());
            container.pop_back();

            return max;
        }

    private:
        std::vector<T> container;
        Compare comparer;
    };

}