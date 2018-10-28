#pragma once

#include <array>
#include <vector>

#include <boost/operators.hpp>

namespace cppchallenge::lang {
    class IPv4 : boost::less_than_comparable<IPv4>,
                 boost::equivalent<IPv4> {
    public:
        IPv4();

        /**
         * Ctor from explicit octets
         * @param o1
         * @param o2
         * @param o3
         * @param o4
         */
        IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);

        /**
         * Ctor from string IPv4 representation
         * @param ip
         */
        explicit IPv4(std::string ip);

        /**
         * Ctor from numeric IPv4 representation
         * @param ip
         */
        explicit IPv4(uint32_t ip);

        /**
         * Creates an IPv4 from string
         * @param input_ip
         * @return this
         */
        IPv4 &from_string(std::string input_ip);

        /**
         * Returns string representation of an IPv$ address
         * @return
         */
        std::string to_string() const;

        /**
         * Returns numeric representation of an IPv4
         * @return
         */
        uint32_t to_num() const;

        IPv4 &operator++();
    private:
        static const int OCTETS_COUNT = 4;

        std::array<uint8_t, OCTETS_COUNT> ip;
    };

    bool operator<(const IPv4 &lhs, const IPv4 &rhs) noexcept;

    std::ostream &operator<<(std::ostream &os, const IPv4 &ipv4);
    std::istream &operator>>(std::istream &is, IPv4 &ipv4);

    /**
     * Creates an IPv4 range from given limits
     * @param first ip
     * @param last ip
     * @return range
     */
    std::vector<IPv4> create_ipv4_range(const IPv4 &first, const IPv4 last);
}
