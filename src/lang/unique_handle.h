#pragma once

#include <algorithm>

namespace cppchallenge::lang {

    /**
     * System call wrapper based on The Modern C++ Challenge implementation by Marius Bancila (which is based on implementation
     * by Kenny Kerr and published in the "Windows With C++ - C++ and the Windows API" article).
     * @tparam Traits
     */
    template<typename Traits>
    class unique_handle {
    private:
        using ptr = typename Traits::ptr;
        ptr _value;

    public:
        unique_handle(const unique_handle &) = delete;

        unique_handle &operator=(const unique_handle &) = delete;

        explicit unique_handle(ptr value = Traits::invalid()) noexcept : _value(value) {};

        unique_handle &operator=(unique_handle &&lhs) noexcept {
            if (this != &lhs) {
                reset(lhs.release());
            }
            return *this;
        }

        ~unique_handle() noexcept {
            Traits::close(_value);
        }

        explicit operator bool() const noexcept {
            return _value != Traits::invalid();
        }

        ptr get() const noexcept {
            return _value;
        }

        ptr release() noexcept {
            auto value = _value;
            _value = Traits::invalid();
            return value;
        }

        bool reset(ptr value = Traits::invalid()) noexcept {
            if (_value != value) {
                Traits::close(_value);
                _value = value;
            }

            return static_cast<bool>(*this);
        }

        void swap(unique_handle<Traits> &handle) noexcept {
            std::swap(_value, handle._value);
        }
    };

    template<typename Traits>
    void swap(unique_handle<Traits> &lhs, unique_handle<Traits> &rhs) noexcept {
        lhs.swap(rhs);
    }

    template<typename Traits>
    bool operator==(const unique_handle<Traits> &lhs, const unique_handle<Traits> &rhs) noexcept {
        return lhs.get() == rhs.get();
    }

    template<typename Traits>
    bool operator!=(const unique_handle<Traits> &lhs, const unique_handle<Traits> &rhs) noexcept {
        return lhs.get() != rhs.get();
    }
}