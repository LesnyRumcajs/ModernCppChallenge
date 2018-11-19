#pragma once

#include <cmath>
#include <boost/operators.hpp>

namespace cppchallenge::lang {
    using deg_t = double;

    /**
     * compares equality of two flaoating-point variables within a given error range
     * @param d1
     * @param d2
     * @param epsilon acceptable error
     * @return
     */
    bool are_equal(const deg_t d1, const deg_t d2, const deg_t epsilon = .001) {
        return std::fabs(d1-d2) < epsilon;
    }

    /**
     * Possible temperature scales
     */
    enum class scale {
        celsius,
        fahrenheit,
        kelvin
    };

    template<scale S>
    class Quantity : boost::less_than_comparable<Quantity<S>, Quantity<S>>,
                     boost::equality_comparable<Quantity<S>>
    {
    public:
        constexpr explicit Quantity(const deg_t amount) : _amount(amount) {}
        explicit operator double() const {
            return _amount;
        }

        bool operator<(const Quantity<S>& rhs) const {
            return _amount < rhs._amount;
        }

        bool operator>(const Quantity<S>& rhs) const {
            return _amount > rhs._amount;
        }

        bool operator==(const Quantity<S>& rhs) const {
            return are_equal(_amount, rhs._amount);
        }
    private:
        const deg_t _amount;
    };

    /**
     * Generic conversion trait
     * @tparam S from type
     * @tparam R to type
     */
    template <scale S, scale R>
    struct conversion_traits {
        static constexpr deg_t convert(const deg_t value) = delete;
    };

    /**
     * Conversion trait from Celsius to Fahrenheit
     */
    template<>
    struct conversion_traits<scale::celsius, scale::fahrenheit> {
        static constexpr deg_t convert(const deg_t value) {
            return (value * 9) / 5 + 32;
        }
    };

    /**
     * Conversion trait from Fahrenheit to Celsius
     */
    template<>
    struct conversion_traits<scale::fahrenheit, scale::celsius> {
        static constexpr deg_t convert(const deg_t value) {
            return (value - 32) * 5 / 9;
        }
    };

    /**
     * Conversion trait from Celsius to Kelvin
     */
    template<>
    struct conversion_traits<scale::celsius, scale::kelvin> {
        static constexpr deg_t convert(const deg_t value) {
            return value + 273.15;
        }
    };

    /**
     * Conversion trait from Fahrenheit to Kelvin
     */
    template<>
    struct conversion_traits<scale::fahrenheit, scale::kelvin> {
        static constexpr deg_t convert(const deg_t value) {
            return (value + 459.67)*5/9;
        }
    };

    /**
     * Conversion trait from Kelvin to Celsius
     */
    template<>
    struct conversion_traits<scale::kelvin, scale::celsius> {
        static constexpr deg_t convert(const deg_t value) {
            return value - 273.15;
        }
    };

    /**
     * Conversion trait from Kelvin to Fahrenheit
     */
    template<>
    struct conversion_traits<scale::kelvin, scale::fahrenheit> {
        static constexpr deg_t convert(const deg_t value) {
            return value*9/5 - 459.67;
        }
    };

    /**
     * Performs conversion between two scales
     * @tparam S from scale
     * @tparam R to scale
     * @param q value in S scale
     * @return value in R scale
     */
    template <scale S, scale R>
    constexpr Quantity<S> temperature_cast(const Quantity<R> q) {
        return Quantity<S>(conversion_traits<R,S>::convert(static_cast<deg_t>(q)));
    }

    constexpr Quantity<scale::celsius> operator"" _deg(const long double amount) {
        return Quantity<scale::celsius> {static_cast<deg_t>(amount)};
    }

    constexpr Quantity<scale::fahrenheit> operator"" _f (const long double amount)  {
        return Quantity<scale::fahrenheit> {static_cast<deg_t>(amount)};
    }

    constexpr Quantity<scale::kelvin> operator"" _k (const long double amount) {
        return Quantity<scale::kelvin> {static_cast<deg_t>(amount)};
    }
}
