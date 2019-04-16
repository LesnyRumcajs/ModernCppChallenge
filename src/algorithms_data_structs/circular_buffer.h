#pragma once

#include <vector>
#include <stdexcept>
#include "circular_iterator.h"

namespace cppchallenge::algorithms_data_structs {
    template<typename T>
    class CircularBuffer {
        using size_type = typename std::vector<T>::size_type;
        using const_iterator = CircularIterator<T>;
    public:
        explicit CircularBuffer(size_type size) : container(size), head(-1), buffer_size(0) {
        }

        bool empty() const noexcept {
            return buffer_size == 0;
        }

        bool full() const noexcept {
            return buffer_size == container.size();
        }

        size_type size() const noexcept {
            return buffer_size;
        }

        size_type capacity() const noexcept {
            return container.size();
        }

        void push(const T &element) {
            head = next();
            container[head] = element;

            if (buffer_size < container.size()) {
                ++buffer_size;
            }
        }

        T pop() {
            if (empty()) {
                throw std::runtime_error("Container empty.");
            }

            auto pos = first();
            --buffer_size;

            return container.at(pos);
        }

        const_iterator begin() const {
            return const_iterator(*this, first(), empty());
        }

        const_iterator end() const {
            return const_iterator(*this, next(), true);
        }


    private:
        std::vector<T> container;
        size_type head;
        size_type buffer_size;

        size_type next() const noexcept {
            if (empty()) {
                return 0;
            }

            return (head + 1) % container.size();
        }

        size_type first() const noexcept {
            if (empty()) {
                return 0;
            }

            return (head + container.size() - buffer_size + 1) % container.size();
        }

        friend class CircularIterator<T>;
    };

}
