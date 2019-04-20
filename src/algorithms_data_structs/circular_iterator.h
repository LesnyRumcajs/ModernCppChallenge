#pragma once

#include "circular_buffer.h"
#include <iterator>
#include <cassert>

namespace cppchallenge::algorithms_data_structs {
    template<typename T>
    class CircularBuffer;

    template<typename T>
    class CircularIterator {
        using self_type = CircularIterator<T>;
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = ptrdiff_t;

    public:
        CircularIterator(const CircularBuffer<T> &buffer, typename CircularBuffer<T>::size_type pos, bool last) :
                buffer(buffer),
                pos(pos),
                last(last) {}

        /**
         * Pre-increment operator
         */
        self_type &operator++() {
            if (last) {
                throw std::out_of_range("Try to access past the range");
            }

            pos = (pos + 1) % buffer.capacity();
            last = pos == buffer.next();

            return *this;
        }

        /**
         * Post-increment operator
         */
        const self_type operator++ (int) {
            self_type tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator== (const self_type& rhs) const {
            assert(compatible(rhs));
            return pos == rhs.pos && last == rhs.last;
        }

        bool operator!= (const self_type& other) const {
            return !(*this == other);
        }

        const_reference operator*() const {
            if (buffer.size() == 0) {
                throw std::out_of_range("Empty buffer!");
            }
            return buffer.container.at(pos);
        }

        const_pointer operator->() const {
            return &**this;
        }

    private:
        const CircularBuffer<T>& buffer;
        typename CircularBuffer<T>::size_type  pos;
        bool last;

        /**
         * Checks if iterator corresponds to the same data structure
         * @param other other iterator
         */
        bool compatible(const self_type& other) const {
            return &buffer== &other.buffer;
        }
    };
}
