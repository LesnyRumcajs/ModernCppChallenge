#include "gray_code.h"

#include <bitset>

std::string cppchallenge::math::dec2binary(uint8_t number) {
    return std::bitset<8>(number).to_string();
}

std::string cppchallenge::math::dec2gray(uint8_t number) {
    uint8_t gray_code = number ^(number >> 1);
    return std::bitset<8>(gray_code).to_string();
}

uint8_t cppchallenge::math::gray2dec(std::string gray) {
    auto num_decimal{0ull};
    auto num_gray = std::bitset<8>(gray).to_ulong();

    for (; num_gray; num_gray = num_gray >> 1)
        num_decimal ^= num_gray;

    return static_cast<uint8_t>(std::bitset<8>(num_decimal).to_ulong());
}
