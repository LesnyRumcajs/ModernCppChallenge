#pragma once

#include <vector>
#include <mutex>
#include <shared_mutex>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Buffer that allows reading it from multiple threads with always complete
     * data (not partially updated).
     */
    template<typename T>
    class DoubleBuffer {
        using size_type = typename std::vector<T>::size_type;
        using reference = typename std::vector<T>::reference;
        using const_reference = typename std::vector<T>::const_reference;
    public:
        explicit DoubleBuffer(const size_type size) : read_buffer(size), write_buffer(size) {
        }

        size_type size() const noexcept {
            return read_buffer.size();
        }

        size_type write(const T *data, const size_type size) {
            std::lock_guard guard(write_mutex);

            auto len = std::min(size, write_buffer.size());
            std::copy(data, data + len, write_buffer.begin());

            std::lock_guard read_guard(read_mutex);
            write_buffer.swap(read_buffer);

            return len;
        }

        template<typename Output>
        void read(Output out, const size_type size) const {
            std::shared_lock lock(read_mutex);

            auto len = std::min(size, read_buffer.size());
            std::copy(read_buffer.begin(), read_buffer.begin() + len, out);
        }

        reference operator[](const size_type index) {
            std::shared_lock lock(read_mutex);
            return read_buffer[index];
        }

        const_reference operator[](const size_type index) const {
            std::shared_lock lock(read_mutex);
            return read_buffer[index];
        }

    private:
        std::vector<T> read_buffer;
        mutable std::shared_mutex read_mutex;

        std::vector<T> write_buffer;
        mutable std::mutex write_mutex;
    };
}