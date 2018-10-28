#pragma once

#include <array>
#include <vector>

namespace cppchallenge::lang {
    class IPv4 {
    public:
        IPv4();

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

    private:
        static const int OCTETS_COUNT = 4;

        std::array<uint8_t, OCTETS_COUNT> ip;
    };


    std::ostream &operator<<(std::ostream &os, const IPv4 &ipv4);

    std::istream &operator>>(std::istream &is, IPv4 &ipv4);
}

