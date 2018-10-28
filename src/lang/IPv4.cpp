#include <sstream>
#include "IPv4.h"

#include <boost/algorithm/string.hpp>

cppchallenge::lang::IPv4::IPv4() {

}

std::string cppchallenge::lang::IPv4::to_string() const {
    std::stringstream ss;
    ss << static_cast<int>(ip[0]);
    for (auto i = 1; i < OCTETS_COUNT; ++i) {
        ss << '.' << static_cast<int>(ip[i]);
    }

    return ss.str();
}

cppchallenge::lang::IPv4 &cppchallenge::lang::IPv4::from_string(std::string input_ip) {
    std::vector<std::string> split_ip;

    boost::split(split_ip, input_ip, [](auto c) {
        return c == '.';
    });

    if (split_ip.size() != OCTETS_COUNT) {
        throw std::invalid_argument("Invalid octet count");
    }

    std::transform(split_ip.begin(), split_ip.end(), ip.begin(), [](auto el) {
        auto octet = std::stoi(el);
        if (octet < 0 || octet > 255) {
            throw std::invalid_argument("Invalid octet");
        }
        return static_cast<uint8_t>(octet);
    });

    return *this;
}

std::istream &cppchallenge::lang::operator>>(std::istream &is, cppchallenge::lang::IPv4 &ipv4) {
    std::string input;
    is >> input;
    ipv4.from_string(std::move(input));
    return is;
}

std::ostream &cppchallenge::lang::operator<<(std::ostream &os, const cppchallenge::lang::IPv4 &ipv4) {
    return os << ipv4.to_string();
}
