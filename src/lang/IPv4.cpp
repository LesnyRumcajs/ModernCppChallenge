#include <sstream>
#include "IPv4.h"

#include <boost/algorithm/string.hpp>

cppchallenge::lang::IPv4::IPv4() :
        ip{0, 0, 0, 0} {
}

cppchallenge::lang::IPv4::IPv4(std::string ip) {
    from_string(std::move(ip));
}

cppchallenge::lang::IPv4::IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4) :
        ip{o1, o2, o3, o4} {
}

cppchallenge::lang::IPv4::IPv4(uint32_t ip_num) :
        ip{static_cast<uint8_t>(ip_num >> 24),
           static_cast<uint8_t>(ip_num >> 16),
           static_cast<uint8_t>(ip_num >> 8),
           static_cast<uint8_t>(ip_num )} {

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

uint32_t cppchallenge::lang::IPv4::to_num() const {
    return (ip[0] << 24 |
            ip[1] << 16 |
            ip[2] << 8 |
            ip[3]);
}

bool cppchallenge::lang::operator<(const cppchallenge::lang::IPv4 &lhs, const cppchallenge::lang::IPv4 &rhs) noexcept {
    return lhs.to_num() < rhs.to_num();
}

cppchallenge::lang::IPv4 &cppchallenge::lang::IPv4::operator++() {
    *this = IPv4(to_num() + 1);
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

std::vector<cppchallenge::lang::IPv4>
cppchallenge::lang::create_ipv4_range(const cppchallenge::lang::IPv4 &first, const cppchallenge::lang::IPv4 last) {
    std::vector<IPv4> result;
    if (last < first) {
        throw std::invalid_argument("Invalid range provided - last element smaller than first!");
    }

    for (auto ip = first; ip <= last; ++ip) {
        result.push_back(ip);
    }

    return result;
}
